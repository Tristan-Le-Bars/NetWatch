# Makefile pour compiler le serveur et le client

# Compilateur et options de compilation
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Fichiers sources et objets pour le serveur
SERVER_SOURCES = src/server.cpp src/console.cpp src/file_tools.cpp
SERVER_HEADERS = headers/server.h headers/console.h headers/file_tools.h
SERVER_OBJECTS = $(SERVER_SOURCES:.cpp=.o)
SERVER_EXEC = server

# Fichiers sources et objets pour le client
CLIENT_SOURCES = src/client.cpp src/file_tools.cpp src/vault_client.cpp
CLIENT_HEADERS = headers/client.h headers/file_tools.h
CLIENT_OBJECTS = $(CLIENT_SOURCES:.cpp=.o)
CLIENT_EXEC = client

# Règle par défaut : compiler tout
all: $(SERVER_EXEC) $(CLIENT_EXEC)

# Compilation du serveur
$(SERVER_EXEC): $(SERVER_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(SERVER_EXEC) $(SERVER_OBJECTS)

# Compilation du client
$(CLIENT_EXEC): $(CLIENT_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(CLIENT_EXEC) $(CLIENT_OBJECTS)

# Règles pour générer les fichiers objets .o à partir des sources .cpp
%.o: %.cpp $(SERVER_HEADERS) $(CLIENT_HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyer les fichiers compilés
clean:
	rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS) $(SERVER_EXEC) $(CLIENT_EXEC)

# Nettoyer les fichiers objets uniquement
clean_obj:
	rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS)

# Règles de phonie pour éviter les erreurs si des fichiers nommés "clean" ou "all" existent
.PHONY: all clean clean_obj