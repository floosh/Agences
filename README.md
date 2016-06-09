# Projet Agences
Projet agences - Cours d'optimisation discrète - Polytech info 4A (2015/2016)  
Implémentation avec GUI d'une métaheuristique de recuit-simulé

### Setup:

Le projet est développé en C++ à l'aide du framework Qt. (http://www.qt.io/)
La compilation dépend donc du système d'exploitation de la machine.

#### 1 - Télécharger le SDK et les bibliothèques selon l'OS

https://www.qt.io/download-open-source/#section-2

#### 2 - Compilation

Avec l'utilitaire qmake pour générer un makefile:
Exemple d'une compilation sous OS.X :

    qmake -project
    qmake -spec macx-g++ myproject.pro
    make  

  
  

#### Alternative avec une GUI

IDE QT Créator - livre par défaut avec le compilateur et le déboggueur  
https://www.qt.io/download-open-source/#section-6  

  
  
### Eventuels problèmes:

Le compilateur doit être en mode de compatibilité C++11, dans le makefile:

    CXXFLAGS=-g -std=c++11
    
dans les flags du compilateur :

    gcc -std=c++11

Et priez Cthulhu ! :

     __
    (oO) 
    /||\ 


  
