# Ejecutar GNU make desde unidad25-construccion.
CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -g -O0
CPPFLAGS =
LDFLAGS =
LDLIBS =
EXE =
# Ubuntu/macOS requieren mkdir del shell. Windows: shell MSYS2 UCRT64.
BUILD = build
COMMON = agenda catalogo sensor archivo entrada
APP = $(BUILD)/agenda_app$(EXE)
TEST = $(BUILD)/pruebas_agenda$(EXE)
OBJECTS = $(addprefix $(BUILD)/,$(addsuffix .o,$(COMMON)))
.PHONY: all test clean
all: $(APP)
$(BUILD):
	mkdir -p $(BUILD)
$(BUILD)/agenda.o: ../unidad23-diseno/proyecto/agenda.c | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@
$(BUILD)/catalogo.o: ../unidad21-recursos/proyecto/catalogo.c | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@
$(BUILD)/sensor.o: ../unidad17-estructuras/proyecto/sensor.c | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@
$(BUILD)/archivo.o: ../unidad19-archivos/proyecto/archivo.c | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@
$(BUILD)/entrada.o: ../unidad16-lineas/proyecto/entrada.c | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@
$(BUILD)/persistencia.o: ../unidad24-aplicacion/proyecto/persistencia.c | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@
$(BUILD)/main.o: ../unidad24-aplicacion/proyecto/main.c | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@
$(BUILD)/pruebas_agenda.o: ../unidad23-diseno/proyecto/pruebas_agenda.c | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@
$(APP): $(BUILD)/main.o $(BUILD)/persistencia.o $(OBJECTS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
$(TEST): $(BUILD)/pruebas_agenda.o $(OBJECTS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
test: $(TEST)
	./$(TEST)
clean:
	rm -f $(BUILD)/*.o $(BUILD)/*.d $(APP) $(TEST)
-include $(wildcard $(BUILD)/*.d)
