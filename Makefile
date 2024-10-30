# Makefile pour compiler le serveur et le client

# Compilateur et options de compilation
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Dossiers des fichiers sources et d'en-tête
CLIENT_SRC_DIR = client/src
CLIENT_HEADER_DIR = client/include
SERVER_SRC_DIR = server/src
SERVER_HEADER_DIR = server/include
SHARED_SRC_DIR = shared/src
SHARED_HEADER_DIR = shared/include

# Fichiers sources et objets pour le serveur
SERVER_SOURCES = $(SERVER_SRC_DIR)/server.cpp $(SERVER_SRC_DIR)/console.cpp $(SHARED_SRC_DIR)/file_tools.cpp
SERVER_OBJECTS = $(SERVER_SOURCES:.cpp=.o)
SERVER_EXEC = server

# Fichiers sources et objets pour le client
CLIENT_SOURCES = $(CLIENT_SRC_DIR)/client.cpp $(CLIENT_SRC_DIR)/vault_client.cpp $(CLIENT_SRC_DIR)/machine_resources.cpp $(SHARED_SRC_DIR)/file_tools.cpp
CLIENT_OBJECTS = $(CLIENT_SOURCES:.cpp=.o)
CLIENT_EXEC = client

# Règle par défaut : compiler tout
all: $(SERVER_EXEC) $(CLIENT_EXEC)

# Compilation du serveur
server: $(SERVER_EXEC)

$(SERVER_EXEC): $(SERVER_OBJECTS)
	$(CXX) $(CXXFLAGS) -I $(SERVER_HEADER_DIR) -I $(SHARED_HEADER_DIR) -o $(SERVER_EXEC) $(SERVER_OBJECTS)

# Compilation du client
client: $(CLIENT_EXEC)

$(CLIENT_EXEC): $(CLIENT_OBJECTS)
	$(CXX) $(CXXFLAGS) -I $(CLIENT_HEADER_DIR) -I $(SHARED_HEADER_DIR) -o $(CLIENT_EXEC) $(CLIENT_OBJECTS)

# Règles pour générer les fichiers objets .o du serveur
$(SERVER_SRC_DIR)/%.o: $(SERVER_SRC_DIR)/%.cpp $(SERVER_HEADER_DIR)/%.h
	$(CXX) $(CXXFLAGS) -I $(SERVER_HEADER_DIR) -I $(SHARED_HEADER_DIR) -c $< -o $@

# Règles pour générer les fichiers objets .o du client
$(CLIENT_SRC_DIR)/%.o: $(CLIENT_SRC_DIR)/%.cpp $(CLIENT_HEADER_DIR)/%.h
	$(CXX) $(CXXFLAGS) -I $(CLIENT_HEADER_DIR) -I $(SHARED_HEADER_DIR) -c $< -o $@

# Règles pour les fichiers objets .o partagés
$(SHARED_SRC_DIR)/%.o: $(SHARED_SRC_DIR)/%.cpp $(SHARED_HEADER_DIR)/%.h
	$(CXX) $(CXXFLAGS) -I $(SHARED_HEADER_DIR) -c $< -o $@

# Nettoyer les fichiers compilés
clean:
	rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS) $(SERVER_EXEC) $(CLIENT_EXEC)

# Nettoyer uniquement les fichiers objets
clean_obj:
	rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS)

# Règles de phonie pour éviter les erreurs si des fichiers nommés "clean" ou "all" existent
.PHONY: all clean clean_obj client server