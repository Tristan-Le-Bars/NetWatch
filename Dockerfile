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

# Définir le port sur lequel le serveur écoute (à ajuster selon votre code)
EXPOSE 8080
EXPOSE 9002

# Compiler le serveur et le client en utilisant le Makefile
RUN make server

# Définir la commande par défaut pour exécuter le serveur (ou client)
CMD ["./netwatch_server"]