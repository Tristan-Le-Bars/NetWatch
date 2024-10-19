# Makefile pour compiler le serveur et le client

# Compilateur et options de compilation
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Dossiers des fichiers sources et d'en-tête
SRC_DIR = src
HEADER_DIR = headers

# Fichiers sources et objets pour le serveur
SERVER_SOURCES = $(SRC_DIR)/server.cpp $(SRC_DIR)/console.cpp $(SRC_DIR)/file_tools.cpp
SERVER_OBJECTS = $(SERVER_SOURCES:.cpp=.o)
SERVER_EXEC = server

# Fichiers sources et objets pour le client
CLIENT_SOURCES = $(SRC_DIR)/client.cpp $(SRC_DIR)/file_tools.cpp $(SRC_DIR)/vault_client.cpp $(SRC_DIR)/machine_resources.cpp
CLIENT_OBJECTS = $(CLIENT_SOURCES:.cpp=.o)
CLIENT_EXEC = client

# Règle par défaut : compiler tout
all: $(SERVER_EXEC) $(CLIENT_EXEC)

server: $(SERVER_EXEC)

# Compilation du serveur
$(SERVER_EXEC): $(SERVER_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(SERVER_EXEC) $(SERVER_OBJECTS)


# Compilation du client
$(CLIENT_EXEC): $(CLIENT_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(CLIENT_EXEC) $(CLIENT_OBJECTS)

# Règles pour générer les fichiers objets .o du serveur à partir des sources .cpp
$(SRC_DIR)/server.o: $(SRC_DIR)/server.cpp $(HEADER_DIR)/server.h $(HEADER_DIR)/console.h $(HEADER_DIR)/file_tools.h
	$(CXX) $(CXXFLAGS) -I $(HEADER_DIR) -c $< -o $@

$(SRC_DIR)/console.o: $(SRC_DIR)/console.cpp $(HEADER_DIR)/console.h
	$(CXX) $(CXXFLAGS) -I $(HEADER_DIR) -c $< -o $@

$(SRC_DIR)/file_tools.o: $(SRC_DIR)/file_tools.cpp $(HEADER_DIR)/file_tools.h
	$(CXX) $(CXXFLAGS) -I $(HEADER_DIR) -c $< -o $@

# Règles pour générer les fichiers objets .o du client à partir des sources .cpp
$(SRC_DIR)/client.o: $(SRC_DIR)/client.cpp $(HEADER_DIR)/client.h $(HEADER_DIR)/file_tools.h
	$(CXX) $(CXXFLAGS) -I $(HEADER_DIR) -c $< -o $@

$(SRC_DIR)/machine_resources.o: $(SRC_DIR)/machine_resources.cpp $(HEADER_DIR)/machine_resources.h
	$(CXX) $(CXXFLAGS) -I $(HEADER_DIR) -c $< -o $@
	
$(SRC_DIR)/vault_client.o: $(SRC_DIR)/vault_client.cpp $(HEADER_DIR)/client.h
	$(CXX) $(CXXFLAGS) -I $(HEADER_DIR) -c $< -o $@


# Nettoyer les fichiers compilés
clean:
	rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS) $(SERVER_EXEC) $(CLIENT_EXEC)

# Nettoyer les fichiers objets uniquement
clean_obj:
	rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS)

# Règles de phonie pour éviter les erreurs si des fichiers nommés "clean" ou "all" existent
.PHONY: all clean clean_obj