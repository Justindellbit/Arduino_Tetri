# *Tetris sur Arduino avec Matrice LED 8x8 (1588AS)*

Ce projet implémente une version simplifiée du jeu *Tetris* sur une *matrice de LED 8x8 (modèle 1588AS), pilotée par un **Arduino Uno*.  
L'affichage est multiplexé manuellement sans l'utilisation du MAX7219.  
Un *potentiomètre B10K* est utilisé pour déplacer les blocs representant le tetri latéralement

---

## *Matériel utilisé :*
- Arduino Uno  
- Matrice LED 8×8 1588AS (cathode commune)  
- Potentiomètre B10K (pour les mouvements gauche/droite)  
-   
- 8 Résistances de limitation si besoin ( LEDs 
- Fils de connexion et breadboard

---

1. *Câblage* : 
   - Branche la *matrice de LED 8x8* aux broches de l'Arduino selon le schéma suivant :
     - *Lignes* : Pin 12, 8, 11, 5, A5, 10, A4, A1
     - *Colonnes* : Pin 7, A3, A2, 3, A0, 4, 6, 9
   - Connecte le *potentiomètre B10K* à l'entrée analogique (A0 par exemple)
---

## *Schéma de câblage :*
Voici un schéma simplifié pour connecter la matrice de LED et le potentiomètre à l'Arduino :
- *Matrice de LED 8x8* :
  - Broches *lignes* et *colonnes* reliées aux pins Arduino comme indiqué ci-dessus.
- *Potentiomètre* : Une borne connectée à *5V, l'autre à **GND, et la borne centrale (wiper) à **A0* pour la lecture analogique.

---

## *Fonctionnalités :*
- *Jeu Tetris* sur la matrice de LED 8x8.
- *Déplacement latéral* des blocs contrôlé par le potentiomètre B10K.
-*Rafraîchissement* de la matrice en arrière-plan utilisant *Timer matériel (Timer2)* pour un affichage fluide.
- *Gestion des collisions* et *effacement des lignes complètes*.

---

## *Code :*
```cpp
// Code Arduino complet pour faire fonctionner le Tetris sur la matrice 8x8
// Voir le fichier dot.ino pour le code complet

void setup() {
  // Configuration des broches et initialisation du jeu
}

#############


void loop() {
  // Logique du jeu : déplacement des pièces, vérification des lignes complètes
}

ISR(TIMER2_COMPA_vect) {
  // Rafraîchissement de la matrice de LED avec multiplexage
}
