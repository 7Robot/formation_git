# Formation Git

Dépôt pour les formations `git` de 7Robot

## Commandes de gestion locale:

* `git init` --> initialise un dépôt git local

* `git branch` --> affiche les branches locales
* `git branch <nom_branche_local>` --> crée la branche locale <nom_branche_local>
* `git branch -d <nom_branche_local>` --> supprime la branche locale <nom_branche_local>

* `git checkout <nom_branche_local>` --> bascule sur la branche locale <nom_branche_local>
* `git checkout -b <nom_branche_local>` --> Crée la branche locale <nom_branche_local> et bascule dessus directement
* `git merge <nom_branche_local>` --> importe les modifications de la branche locale <nom_branche_local> sur la branche actuelle
* `git status` --> montre les fichiers modifiés et/ou non suivis
* `git add .` --> ajoute toutes les modifications locales au commit
* `git restore <fichier>` --> restore le fichier <fichier> à son état lors du commit local précédent (supprime définitvement les changements non commit)
* `git commit -m "Message"` --> crée le commit local avec les fichiers modifiés avec comme description "Message"
* `git stash` --> enregistre les modifications, mais ne les applique pas (remisage)
* `git stash list` --> liste les remisages
* `git stash apply <nom_stash>` --> réapplique le remisage <nom_stash>
* `git reset HEAD` --> annule tous les changements depuis la dernière synchronisation avec le dépôt distant
* `git reset HEAD <fichier>` --> annule la modification sur le fichier <fichier> depuis la dernière synchronisation avec le dépôt distant
* Commandes de gestion distante :
* `git clone` URL <dépôt> --> clone le dépôt distant à l'adresse URL vers le répertoire cible <dépôt>
* `git remote add origin https://github.com/<utilisateur>/<dépôt>.git` --> configure le dépôt local pour suivre le dépôt distant à l'adresse https://github.com/<utilisateur>/<dépôt>.git
* `git fetch` --> synchronise les dépôts, à faire avant chaque opération qui concerne le dépôt distant
* `git merge` --> fusionne la branche distante sur la branche locale actuelle
* `git branch` -r --> affiche les branches distantes
* `git branch <nom_branche_local> origin/<nom_branche_distante>` --> crée la branche locale <nom_branche_local> qui est une copie de la branche distante <nom_branche_distante>
* `git push` --> envoie les modifications locales sur la branche distante
* `git push --set-upstream origin <nom_branche_distante>` --> configure la branche distante <nom_branche_distante> pour suivre la branche locale actuelle
* `git push origin :<nom_branche>` --> supprime la branche distante
* `git rm --cached <fichier>` --> supprime l'index du fichier <fichier>
