CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lrt -lpthread

# Ejecutables
EXEC_DATASET = datasetToBin
EXEC_HASH = createBinHashTable
EXEC_SERVER = servidor_busqueda
EXEC_CLIENT = p2-dataProgram

.PHONY: all clean

# Compilar, preparar base de datos, ejecutar y limpiar
all: compilar preparar ejecutar limpiar

compilar:
	@echo "Compilando programas..."
	@$(CC) $(CFLAGS) datasetToBin.c -o $(EXEC_DATASET)
	@$(CC) $(CFLAGS) createBinHashTable.c -o $(EXEC_HASH)
	@$(CC) $(CFLAGS) servidor_busqueda.c -o $(EXEC_SERVER) $(LDFLAGS)
	@$(CC) $(CFLAGS) p2-dataProgram.c -o $(EXEC_CLIENT) $(LDFLAGS)
	@echo ""

preparar:
	@if [ ! -f songs.bin ]; then \
		echo "Convirtiendo CSV a binario..."; \
		./$(EXEC_DATASET); \
		echo ""; \
	fi
	@if [ ! -f hashTableSongs.bin ]; then \
		echo "Creando tabla hash..."; \
		./$(EXEC_HASH); \
		echo ""; \
	fi

ejecutar:
	@tmux split-window -h
	@echo "Iniciando servidor..."
	@tmux send-keys -t 0 "./$(EXEC_SERVER)" C-m
	@echo "Iniciando cliente..."
	@tmux send-keys -t 1 "./$(EXEC_CLIENT)" C-m

limpiar:
	@echo ""
	@echo "Limpiando..."
	@rm -f $(EXEC_DATASET) $(EXEC_HASH)
	@rm -f /dev/shm/song_search_shm /dev/shm/sem.sem_*
	@echo "Listo"

clean:
	@rm -f $(EXEC_DATASET) $(EXEC_HASH) $(EXEC_SERVER) $(EXEC_CLIENT)
	@rm -f songs.bin hashTableSongs.bin
	@rm -f /dev/shm/song_search_shm /dev/shm/sem.sem_*
	@echo "Todo limpio"
