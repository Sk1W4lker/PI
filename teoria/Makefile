CC      ?= gcc
CFLAGS  ?= -std=c11 -O2 -g -Wall -Wextra -Wpedantic
LDFLAGS ?=

# programas a compilar
ALL := \
  running \
  1_hello \
  2_hello_fail \
  3_tipos_variaveis \
  4_tamanhos_tipos \
  5_operadores_int \
  6_calculo_nota \
  7_undefined \
  8_calculo_nota_int \
  9_condicoes \
  10_while \
  11_while_break_continue \
  12_for \
  13_overflow \
  14_scanf \
  15_mini_calculator \
  16_mini_calculator2

#------------------------------------------------------------------------------
# compilar
.PHONY: all print-all clean

all: $(ALL)

print-all:
	@echo $(ALL)

# caso especial: compilar sem -Wall/-Wextra etc
t1_undefined: t1_undefined.c
	$(CC) -std=c11 -O2 -g $(LDFLAGS) -o $@ $<

# caso genérico
$(ALL):
%: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

# remover executáveis
clean:
	$(RM) -f $(ALL)

#------------------------------------------------------------------------------
#-- formatação e checks 
ALL_INDENT := $(addprefix indent-, $(ALL))
ALL_TIDY := $(addprefix tidy-, $(ALL))
ALL_CHECK := $(addprefix check-, $(ALL))

.PHONY: indent-all tidy-all check-all

## sudo apt install indent // ou equivalente dependendo do sistema operativo
indent-all: $(ALL_INDENT)
$(ALL_INDENT):
indent-%:
	indent -kr -nut -i2 $*.c
	$(RM) -f $*.c~

## sudo apt install clang-tidy // ou equivalente dependendo do sistema operativo
tidy-all: $(ALL_TIDY)
$(ALL_TIDY):
tidy-%:
	clang-tidy $*.c -- $(CFLAGS)

## sudo apt install cppcheck // ou equivalente dependendo do sistema operativo
check-all: $(ALL_CHECK)
$(ALL_CHECK):
check-%:
	cppcheck --enable=warning,style,performance,portability --std=c11 --quiet $*.c