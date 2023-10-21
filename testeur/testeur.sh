#!/bin/bash

print_green() {
    echo -e "\033[0;32m$1\033[0m"
}

print_red() {
    echo -e "\033[0;31m$1\033[0m"
}

values=(
#   # test invalide signe
#  "-1 800 200 200"
#  "5 -800 200 200 7"
#  "4 310 -200 100"
#  "5 150 100 -30000"
#   # test invalide lettre
#  "p1 800 200 200"
#  "5 l800 200 200 7"
#  "4 310 s200 100"
#  "5 150 100 i30000"
#   # test trop et pas assez de parametres
#  "1 800 200 200 74 12"
#  "5 800 200 200 7 13 25 47 89"
#  "4 310 200 100 14 14 14 14 14 14 14"
#  "5 150 100"
#  "5 150"
#  "4"
  # test court du sujet
 "1 800 200 200"
 "5 800 200 200 7"
 "4 310 200 100"
 "5 150 100 30000"
)

# test long
# values=(
#   "5 800 200 200" 
#   "4 410 200 200"
#   "5 910 300 150"
# )

# Création du dossier principal pour stocker tous les résultats
mkdir -p test_results

for ((i=0; i<${#values[@]}; i++)); do
  # Création d'un dossier pour chaque combinaison d'arguments basé sur les paramètres
  test_folder="test_results/test_${values[$i]// /_}" # Remplace les espaces par des underscores
  mkdir -p ${test_folder}/results
  mkdir -p ${test_folder}/summaries
  # Affichage du test en cours
  echo "test ${i}: ./philo ${values[$i]}"

  # Exécution du programme philo avec les arguments courants
  # Test 1 : Valgrind avec --leak-check=full
  valgrind --leak-check=full --show-leak-kinds=all -s ./philo ${values[$i]} > /dev/null 2> ${test_folder}/results/r_leak_check.txt
  # Test 1.1 : Check memory
  grep "total heap usage" ${test_folder}/results/r_leak_check.txt > ${test_folder}/summaries/s_leak_check_memory.txt

  allocs=$(grep "total heap usage" ${test_folder}/summaries/s_leak_check_memory.txt | awk -F':' '{print $2}' | awk '{print $1}')
  frees=$(grep "total heap usage" ${test_folder}/summaries/s_leak_check_memory.txt | awk -F':' '{print $2}' | awk '{print $3}')
  
  if [ "$allocs" == "$frees" ]; then
    print_green "valgrind leak-memory: OK"
  else
    print_red "valgrind leak-memory: KO"
  fi

  # Test 1.2 : Check errors
  grep "ERROR SUMMARY" ${test_folder}/results/r_leak_check.txt > ${test_folder}/summaries/s_leak_check_errors.txt
  if grep -q "ERROR SUMMARY: 0 errors from 0 contexts" ${test_folder}/summaries/s_leak_check_errors.txt; then
    print_green "valgrind leak-errors: OK"
  else
    print_red "valgrind leak-errors: KO"
  fi

  # Test 2 : Valgrind avec --tool=helgrind
  valgrind --tool=helgrind -q -s ./philo ${values[$i]} > /dev/null 2> ${test_folder}/results/r_helgrind.txt
  grep "ERROR SUMMARY" ${test_folder}/results/r_helgrind.txt > ${test_folder}/summaries/s_helgrind.txt
  
  if grep -q "ERROR SUMMARY: 0 errors from 0 contexts" ${test_folder}/summaries/s_helgrind.txt; then
    print_green "valgrind tool=helgrind: OK"
  else
    print_red "valgrind tool=helgrind: KO"
  fi
  
  # Test 3 : Valgrind avec --tool=drd
  valgrind --tool=drd -s ./philo ${values[$i]} > /dev/null 2> ${test_folder}/results/r_drd.txt
  grep "ERROR SUMMARY" ${test_folder}/results/r_drd.txt > ${test_folder}/summaries/s_drd.txt
  
  if grep -q "ERROR SUMMARY: 0 errors from 0 contexts" ${test_folder}/summaries/s_drd.txt; then
    print_green "valgrind tool=drd: OK"
  else
    print_red "valgrind tool=drd: KO"
  fi
  echo ""

done

