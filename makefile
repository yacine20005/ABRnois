# Programme et options de compilation
PROG = abrnois
CC = gcc
CFLAGS = -Wall -g -Iinc
LDFLAGS = -lm

# Lister tous les fichiers source .c et les fichiers objets .o
SOURCES = $(wildcard src/*.c) # Utilise le wildcard pour trouver tous les fichiers .c dans le dossier src
OBJETS = $(SOURCES:src/%.c=obj/%.o) # Y inscrit les fichiers objets à l'aide des fichiers trouver dans src
OBJ_DIR = obj

# Règle principale - compile tout le projet
tout: creer_dossier $(PROG)

# Créer le dossier pour les fichiers objets
creer_dossier:
	@mkdir -p obj

# Règle pour s'assurer que le dossier obj existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compiler le programme final
$(PROG): $(OBJETS)
	@echo "🔨 Création du programme $(PROG)..."
	$(CC) -o $(PROG) $(OBJETS) $(LDFLAGS)
	@echo "✅ Programme compilé avec succès!"
	@echo " "

# Règle pour compiler chaque fichier source en fichier objet
obj/%.o: src/%.c | $(OBJ_DIR)
	@echo "📝 Compilation de $<..."
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "✅ Fichier $< compilé avec succès!"
	@echo " "

# Exécuter le programme
lancer: $(PROG)
	@echo "🚀 Lancement du programme $(PROG)..."
	./$(PROG)

# Nettoyer les fichiers compilés
clean:
	@echo "🧹 Nettoyage des fichiers générés..."
	rm -f obj/*.o $(PROG)
	@echo "✨ Nettoyage terminé!"
	@echo " "

# Aide - affiche les commandes disponibles
aide:
	@echo "Commandes disponibles:"
	@echo "  make tout      - compile le programme"
	@echo "  make lancer    - lance le programme"
	@echo "  make clean  - supprime les fichiers compilés"
	@echo "  make aide      - affiche cette aide"

# Ces commandes sont des noms, pas des fichiers
.PHONY: tout creer_dossier lancer clean aide