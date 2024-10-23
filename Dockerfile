# Utiliser une image de base contenant g++ et make
FROM gcc:latest

# Créer un répertoire de travail dans le conteneur
WORKDIR /app

# Copier les fichiers sources et d'en-tête dans les répertoires appropriés
COPY ./src/ /app/src/
COPY ./headers/ /app/headers/
COPY Makefile /app/

# Définir le répertoire de travail pour la compilation
WORKDIR /app

# Compiler le serveur et le client en utilisant le Makefile
RUN make all

# Définir le port sur lequel le serveur écoute (à ajuster selon votre code)
EXPOSE 8080

# Définir la commande par défaut pour exécuter le serveur (ou client)
CMD ["./server"]