import sys
import random

# this code has been made for 7robot

class Game:
    '''
    Class principale pour la gestion du jeu
    '''
    def __init__(self):
        self.io = IO()
        self.rng = random.Random(self.io.seed)
        self.ally = Personnage(self.io.name, 50, self.rng.randrange(1, 10), self.rng.randrange(20, 25))
        self.enemy = Personnage('GitBoss', 50, self.rng.randrange(1, 10), self.rng.randrange(20, 25))

    def run(self):
        self.io.start(self.ally, self.enemy)

        while self.ally.is_alive() and self.enemy.is_alive():
            action = self.io.get_action()
            if action == 'A':
                r = self.ally.attack(self.enemy)
            elif action == 'S':
                r = self.ally.heal()
            elif action == 'AM':
                r = self.ally.attack_magik(self.enemy, 5)
            else:
                sys.exit(-1)

            self.io.print_action(self.ally, self.enemy, (action, r))

            r = self.enemy.attack(self.ally)

            self.io.print_action(self.enemy, self.ally, (action, r))
        if self.ally.is_alive():
            self.io.victory(self.ally)
        else:
            self.io.victory(self.enemy)
        return 0

class IO:
    '''
    Class qui gère les intéractions avec l'utilisateur
    Équipe A: Ajouter des fonctionnalités ici
    Idées:
    Modifier la sélection de la seed
    Modifier la gestion des actions (plus robuste)
    ...
    '''

    def __init__(self):
        print('Bienvenue dans le RPG git formation')
        self.name = input('Choisi ton nom:\n')
        self.seed = input('Choisi un nombre:\n')
        self.step = 0

    def start(self, ally, enemy):
        print(f'Le combat commence entre {ally.name} and {enemy.name}')

    def print_action(self, attacker, defenser, action):
        self.step += 1
        print(f'=== Tour {self.step} ===')
        if action[0] == 'A':
            print(f'\t{attacker.name} attaque.\n'
                  f'\t{defenser.name} subit {action[1]} dégat'
                  f'\tIl reste {defenser.health} à {defenser.name}')
        elif action[0] == 'S':
            print(f'\t{attacker.name} se soigne de {action[1]}')
        elif action[0] == 'AM':
            print(f'\t{attacker.name} attaque.\n'
                  f'\t{defenser.name} subit {action[1]} dégat'
                  f'\tIl reste {defenser.health} à {defenser.name}')

    def get_action(self):
        print('Choisi ton action:')
        print('\tAttaquer: A')
        print('\tSe soigner: S')
        choix = ''
        while not choix in ['A', 'a', 'S', 's', 'AM']:
            choix = input()

        return choix.upper()

    def victory(self, winner):
        print(f'{winner.name} gagne après {self.step} tours')


class Personnage:
    '''
    Personnage du jeu
    Équipe B: Ajouter des fonctionnalités ici
    Idée:
    Attaque magique et physique
    Ajouter de l'aléa dans les dégats
    '''
    def __init__(self, name, health, damage, mana):
        self.name = name
        self.health = health
        self.damage = damage
        self.mana = mana

    def attack(self, other):
        other.take_damage(self.damage)
        return self.damage

    def heal(self):
        self.health += 5
        return 5

    def take_damage(self, damage):
        self.health -= damage

    def is_alive(self):
        return self.health > 0

    def attack_magik(self, other, cout):
        if self.mana >= cout:
            self.mana -= cout
            other.take_damage(self.damage + cout)
            return self.damage + cout
        else:
            return 0



def main():
    game = Game()
    game.run()

if __name__ == '__main__':
    sys.exit(main())
