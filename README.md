# 🍽️ Philosophers

## 📋 Description

Le projet **Philosophers** est une implémentation du célèbre problème des philosophes dîneurs en programmation concurrente. Ce projet explore les concepts fondamentaux de la synchronisation des threads, de la gestion des ressources partagées et de la prévention des interblocages (deadlocks).

### Le Problème des Philosophes

Le problème consiste en N philosophes assis autour d'une table circulaire. Chaque philosophe alterne entre trois états : **penser**, **manger** et **dormir**. Pour manger, un philosophe doit prendre deux fourchettes (une à sa gauche et une à sa droite). Le défi est d'éviter les situations de famine et d'interblocage.

## 🚀 Fonctionnalités

- ✅ Simulation multi-threadée avec pthreads
- ✅ Gestion sécurisée des ressources partagées avec des mutex
- ✅ Prévention des deadlocks et race conditions
- ✅ Monitoring en temps réel de l'état des philosophes
- ✅ Détection automatique de la mort par famine
- ✅ Support pour un nombre variable de philosophes
- ✅ Gestion optionnelle du nombre maximum de repas

## 🛠️ Compilation

```bash
make
```

Le Makefile compile automatiquement tous les fichiers sources et génère l'exécutable `philo`.

## 📖 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Paramètres

| Paramètre | Description | Unité |
|-----------|-------------|-------|
| `number_of_philosophers` | Nombre de philosophes (et de fourchettes) | - |
| `time_to_die` | Temps maximum sans manger avant de mourir | millisecondes |
| `time_to_eat` | Temps nécessaire pour manger | millisecondes |
| `time_to_sleep` | Temps de sommeil | millisecondes |
| `number_of_times_each_philosopher_must_eat` | Nombre de repas requis (optionnel) | - |

### Exemples

```bash
# 5 philosophes, meurent après 800ms sans manger
./philo 5 800 200 200

# 4 philosophes, chacun doit manger 3 fois
./philo 4 410 200 200 3

# Cas limite : 1 philosophe
./philo 1 800 200 200
```

## 🏗️ Architecture

### Structure du Projet

```
philosopher/
├── include/
│   └── philosopher.h          # Définitions des structures et prototypes
├── src/
│   ├── init/                  # Modules d'initialisation
│   │   ├── init.c            # Initialisation générale
│   │   ├── init_mutex.c      # Initialisation des mutex
│   │   └── init_philosopher.c # Initialisation des philosophes
│   ├── philo/                 # Logique principale
│   │   ├── philosopher.c     # Point d'entrée du programme
│   │   ├── thread_1.c        # Gestion des threads (partie 1)
│   │   ├── thread_2.c        # Gestion des threads (partie 2)
│   │   ├── eating.c          # Logique de prise de repas
│   │   ├── death.c           # Détection de mort
│   │   ├── death_eating.c    # Conditions d'arrêt par repas
│   │   └── free_mutex.c      # Libération des mutex
│   └── utils/                 # Fonctions utilitaires
│       ├── parsing.c         # Validation des arguments
│       ├── utils_parsing.c   # Utilitaires de parsing
│       ├── error.c           # Gestion d'erreurs
│       ├── free.c            # Libération mémoire
│       └── utils.c           # Fonctions génériques
├── testeur/                   # Scripts de test
│   ├── testeur.sh            # Tests automatisés
│   └── testeur2.sh           # Tests supplémentaires
└── Makefile                   # Configuration de compilation
```

### Structures de Données Principales

#### `t_data`
Structure centrale contenant tous les paramètres de simulation et les ressources partagées.

#### `t_phi`
Représente un philosophe individuel avec son ID, son thread et le timestamp de son dernier repas.

#### `t_state`
Énumération des états possibles d'un philosophe :
- `THINKING` : En train de penser
- `EATING` : En train de manger
- `SLEEPING` : En train de dormir
- `TAKEN_FORK` : A pris une fourchette
- `DIED` : Mort de faim

## 🔧 Algorithme

### Stratégie Anti-Deadlock

Le programme implémente plusieurs stratégies pour éviter les interblocages :

1. **Ordre de prise des fourchettes** : Les philosophes pairs et impairs prennent les fourchettes dans un ordre différent
2. **Timeouts** : Surveillance continue du temps écoulé depuis le dernier repas
3. **Monitoring centralisé** : Un thread principal surveille l'état de tous les philosophes

### Cycle de Vie d'un Philosophe

```
THINKING → TAKEN_FORK → TAKEN_FORK → EATING → SLEEPING → THINKING
    ↓                                                        ↑
   DIED ←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←
```

## 🧪 Tests

Le projet inclut des scripts de test automatisés :

```bash
# Exécuter les tests de base
./testeur/testeur.sh

# Exécuter les tests avancés
./testeur/testeur2.sh
```

### Cas de Test Recommandés

| Test | Commande | Résultat Attendu |
|------|----------|------------------|
| Mort assurée | `./philo 1 800 200 200` | Le philosophe meurt |
| Pas de mort | `./philo 5 800 200 200` | Simulation continue |
| Arrêt par repas | `./philo 5 800 200 200 7` | Arrêt après 7 repas chacun |
| Cas limite | `./philo 4 310 200 100` | Test de limites temporelles |

## 🐛 Gestion d'Erreurs

Le programme gère robustement les erreurs suivantes :

- ❌ Arguments invalides (non-numériques, négatifs, overflow)
- ❌ Échec d'allocation mémoire
- ❌ Échec de création de threads ou mutex
- ❌ Paramètres temporels incohérents

## 🔍 Debugging

### Messages de Log

Le programme affiche en temps réel l'état des philosophes :

```
[timestamp_ms] philosopher_id has taken a fork
[timestamp_ms] philosopher_id is eating
[timestamp_ms] philosopher_id is sleeping
[timestamp_ms] philosopher_id is thinking
[timestamp_ms] philosopher_id died
```

### Conseils de Debug

- Utilisez `valgrind` pour détecter les fuites mémoire
- Compilez avec `-fsanitize=thread` pour détecter les race conditions
- Ajustez les paramètres temporels pour tester différents scénarios

## 📚 Concepts Techniques

### Threading
- **pthreads** : Utilisation de la bibliothèque POSIX threads
- **Synchronisation** : Mutex pour protéger les ressources critiques
- **Race Conditions** : Prévention par verrouillage approprié

### Gestion Mémoire
- Allocation dynamique sécurisée
- Libération systématique des ressources
- Gestion des erreurs d'allocation

### Algorithmes de Concurrence
- Prévention des deadlocks
- Équité dans l'accès aux ressources
- Monitoring temps réel

## 👥 Auteurs

**Etienne** - [edesaint@student.42.fr](mailto:edesaint@student.42.fr)

## 📄 Licence

Ce projet est développé dans le cadre du cursus de l'École 42.

---

*Ce projet illustre les défis fondamentaux de la programmation concurrente et constitue une excellente introduction aux concepts de synchronisation en informatique.*
