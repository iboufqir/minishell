# Minishell
Minishell est une version simplifiée d’un interpréteur de commandes UNIX, développée dans le cadre du cursus de l’école 42. Ce projet vise à recréer un shell minimaliste capable de gérer des commandes, des redirections, des pipes, et des variables d’environnement.

# ⚙️ Fonctionnalités
Exécution de programmes avec arguments

Commandes intégrées : cd, echo, pwd, export, unset, env, exit

Gestion des pipes |

Redirections : <, >, >>, << (heredoc)

Expansion des variables d’environnement : $VAR, $?, etc.

Gestion des signaux : Ctrl+C, Ctrl+\

Gestion des erreurs et fuite de mémoire

# ▶️ Lancer le shell
    ´´´bash
    make
    ./minishell

# 🔍 Fonctionnement général
Lecture de la commande avec readline

Parsing et découpage des tokens

Gestion des quotes, des redirections et des variables

Exécution des builtins ou de programmes via fork et execve

# 📚 Compétences acquises
Manipulation de processus (fork, execve, wait)

Gestion des signaux

Parsing avancé

Gestion des fichiers et des descripteurs

Utilisation des listes chaînées et gestion mémoire

# 🙏 Remerciements
Un grand merci à mon binôme **Ahmed Omari** pour son engagement, sa rigueur et l'esprit d'équipe tout au long du développement de ce projet. Son professionnalisme a été un véritable atout dans la réussite de ce minishell.
