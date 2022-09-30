CXX = g++
CC  = $(CXX)

CXXFLAGS = -std=c++11

CXXFLAGS += -pedantic -Wall
CXXFLAGS += -g

all:: testVecteur testGrain testObstacle testSource exerciceP8 exerciceP9 chute_libre

testVecteur: testVecteur.o Vecteur3D.o

testGrain: testGrain.o Vecteur3D.o Case.o Grain.o Obstacle.o

testObstacle: testObstacle.o Vecteur3D.o Obstacle.o

testSource: testSource.o Vecteur3D.o Case.o Grain.o Obstacle.o Aleatoire.o Source.o

exerciceP8: exerciceP8.o Vecteur3D.o Case.o Grain.o Obstacle.o Aleatoire.o Source.o Environnement.o Systeme.o

exerciceP9: exerciceP9.o Vecteur3D.o Case.o Grain.o Obstacle.o Aleatoire.o Source.o Environnement.o Systeme.o TextViewer.o

chute_libre: chute_libre.o Vecteur3D.o Case.o Grain.o Obstacle.o Aleatoire.o Source.o Environnement.o Systeme.o TextViewer.o
