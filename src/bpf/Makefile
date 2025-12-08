COLOR_RESET=\033[0m
COLOR_BOLD=\033[1m

define print
	@printf "$(COLOR_BOLD)  %-6s$(COLOR_RESET) %s\n" "$(1)" "$(2)"
endef

CC = clang

BUILD_DIR := $(CURDIR)/build
BPF_SRC_DIR := .
LIBBPF_HEADERS := ../../external/libbpf/src/install-dir/usr/include
BPF_FLAGS := -I$(LIBBPF_HEADERS) -target bpf -O2 -g -Wall

BPF_SOURCES := $(shell find $(BPF_SRC_DIR) -name '*.c')
BPF_HEADERS := $(shell find $(BPF_SRC_DIR) -name '*.h')

all: $(BUILD_DIR)/main.bpf.o 
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.bpf.o: $(BPF_SOURCES) $(BPF_HEADERS) | $(BUILD_DIR)
	$(call print,BPF,$(BPF_SRC_DIR)/main.bpf.c)
	@$(CC) $(BPF_FLAGS) -c -o $@ $(BPF_SRC_DIR)/main.bpf.c

clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all clean