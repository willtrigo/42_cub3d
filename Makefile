# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 19:55:51 by dande-je          #+#    #+#              #
#    Updated: 2025/02/18 20:03:53 by maurodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#******************************************************************************#
#                                REQUIREMENTS                                  #
#******************************************************************************#

MLX42_VERSION                   := 2.4.1
CMAKE_VERSION                   := 3.16

#******************************************************************************#
#                                   COLOR                                      #
#******************************************************************************#

RED                             := \033[0;31m
GREEN                           := \033[0;32m
YELLOW                          := \033[0;33m
PURPLE                          := \033[0;35m
CYAN                            := \033[0;36m
RESET                           := \033[0m

#******************************************************************************#
#                                   PATH                                       #
#******************************************************************************#

SRCS_MAIN_DIR                   := src/
SRCS_CORE_DIR                   := $(SRCS_MAIN_DIR)core/
SRCS_GRAPHIC_DIR                := $(SRCS_MAIN_DIR)graphic/
SRCS_INFRASTRUCTURE_DIR         := $(SRCS_MAIN_DIR)infrastructure/
SRCS_CONFIG_DIR                 := $(SRCS_INFRASTRUCTURE_DIR)config/
SRCS_PARSE_DIR                  := $(SRCS_CONFIG_DIR)parse/
SRCS_UTILS_DIR                  := $(SRCS_MAIN_DIR)utils/
SRCS_TEST_DIR                   := test/
INCS                            := src/ lib/libftx/includes/ lib/MLX42/include/
BUILD_DIR                       := build/
MLX42_DIR                       := lib/MLX42/
MLX42_BUILD_DIR                 := lib/MLX42/build/
LIBFTX_DIR                      := lib/libftx/
BIN_DIR                         := bin/

#******************************************************************************#
#                                  COMMANDS                                    #
#******************************************************************************#

RM                              := rm -rf
MKDIR                           := mkdir -p
MAKEFLAGS                       += --no-print-directory
SLEEP                           := sleep 0.01

#******************************************************************************#
#                                   FILES                                      #
#******************************************************************************#

LIBFTX = $(addprefix $(LIBFTX_DIR), libft.a)
MLX42 = $(addprefix $(MLX42_BUILD_DIR), libmlx42.a)
LIBS                            := ./lib/libftx/libft.a \
								   ./lib/MLX42/build/libmlx42.a

NAME                            = cub3D
NAME_PATH                       = $(BIN_DIR)$(NAME)
NAME_TEST                       = test_$(NAME)
NAME_TEST_PATH                  = $(BIN_DIR)$(NAME_TEST)


SRCS_MAIN                       = $(addprefix $(SRCS_MAIN_DIR), main.c)
SRCS_FILES                      += $(addprefix $(SRCS_CORE_DIR), game.c)
SRCS_FILES                      += $(addprefix $(SRCS_GRAPHIC_DIR), render.c)
SRCS_FILES                      += $(addprefix $(SRCS_CONFIG_DIR), config.c)
SRCS_FILES                      += $(addprefix $(SRCS_PARSE_DIR), parse_color.c \
								   parse_file.c)
SRCS_FILES                      += $(addprefix $(SRCS_UTILS_DIR), color.c \
								   ft_extensions.c \
								   output.c)
SRCS_FILES                      += $(addprefix $(SRCS_MAIN_DIR), cube.c)

OBJS_MAIN                       = $(SRCS_MAIN:%.c=$(BUILD_DIR)%.o)
OBJS                            += $(SRCS_FILES:%.c=$(BUILD_DIR)%.o)

SRCS_TEST_FILES                 += $(addprefix $(SRCS_TEST_DIR), test_suite.c)
OBJS_TEST                       += $(SRCS_TEST_FILES:%.c=$(BUILD_DIR)%.o)

DEPS                            := $(OBJS:.o=.d)

#******************************************************************************#
#                               OUTPUTS MESSAGES                               #
#******************************************************************************#

COUNT                           = 0
CLEAN_MESSAGE                   := $(NAME) objects deleted
CLEAN_MLX42_OBJS_MESSAGE        := Library MLX42 objects deleted
CLEAN_MLX42_MESSAGE             := Library MLX42 deleted
FCLEAN_MESSAGE                  := $(NAME) deleted
EXE_MESSAGE                     = $(RESET)[100%%] $(GREEN)Built target $(NAME)
COMP_MESSAGE                    = Building C object

#******************************************************************************#
#                               COMPILATION                                    #
#******************************************************************************#

CC                             := cc
CFLAGS                         = -Wall -Wextra -g3
# CFLAGS                         = -Wall -Wextra -Werror -Ofast
CPPFLAGS                       := $(addprefix -I,$(INCS)) -MMD -MP
DFLAGS                         := -g3
LFLAGS                         := -march=native
LDFLAGS                        := $(addprefix -L,$(dir $(LIBS)))
LDLIBS                         := -lft -lmlx42 -ldl -lglfw -pthread -lm
COMPILE_OBJS                   = $(CC) $(CFLAGS) $(LFLAGS) $(CPPFLAGS) -c $< -o $@
COMPILE_EXE                    = $(CC) $(LDFLAGS) $(OBJS_MAIN) $(OBJS) $(LDLIBS) -o $(NAME_PATH)

#******************************************************************************#
#                                   DEFINE                                     #
#******************************************************************************#

ifdef WITH_DEBUG
	CFLAGS += $(DFLAGS)
endif

#******************************************************************************#
#                                  FUNCTION                                    #
#******************************************************************************#

define create_dir
	$(MKDIR) $(BIN_DIR)
	$(MKDIR) $(dir $@)
endef

define submodule_update_mlx42
	printf "$(PURPLE)Building library MLX42\n$(RESET)"
	git submodule update --init --recursive >/dev/null 2>&1 || true
	git submodule foreach -q --recursive \
		'branch="$(git config -f $toplevel/.gitmodules submodule.MLX42)"; \
		git pull origin master; \
		git fetch; \
		git checkout v$(MLX42_VERSION)' \
		>/dev/null 2>&1 || true
	sed -i 's/3\.18/$(CMAKE_VERSION)/g' $(MLX42_DIR)CMakeLists.txt >/dev/null 2>&1 || true
	$(SLEEP)
	cd $(MLX42_DIR) && cmake -B build -DDEBUG=1 >/dev/null 2>&1 || true
	cd $(MLX42_DIR) && cmake --build build -j4
	cd $(MLX42_DIR) && git restore CMakeLists.txt >/dev/null 2>&1 || true
endef

define submodule_update_libftx
	printf "$(PURPLE)Building library Libftx\n$(RESET)"
	git submodule update --init --recursive >/dev/null 2>&1 || true
	git submodule foreach -q --recursive \
		'branch="$(git config -f $toplevel/.gitmodules submodule.submodule_update_libft)"; \
		git pull origin main; \
		git fetch;' \
		>/dev/null 2>&1 || true
	$(SLEEP)
	$(MAKE) -C $(LIBFTX_DIR)
endef

define comp_objs
	$(eval COUNT=$(shell expr $(COUNT) + 1))
	$(COMPILE_OBJS)
	$(SLEEP)
	printf "[%3d%%] $(YELLOW)$(COMP_MESSAGE) $@ \r$(RESET)\n" $$(echo $$(($(COUNT) * 100 / $(words $(OBJS)))))
endef

define comp_exe
	$(COMPILE_EXE)
	$(SLEEP)
	printf "$(EXE_MESSAGE)\n$(RESET)"
endef

define clean
	$(RM) $(BUILD_DIR)
	$(MAKE) fclean -C $(LIBFTX_DIR)
	$(RM) $(MLX42_BUILD_DIR)
	printf "$(RED)$(CLEAN_MLX42_OBJS_MESSAGE)\n$(RESET)"
	printf "$(RED)$(CLEAN_MLX42_MESSAGE)\n$(RESET)"
	$(SLEEP)
	printf "$(RED)$(CLEAN_MESSAGE)\n$(RESET)"
endef

define fclean
	$(RM) $(BIN_DIR)
	$(SLEEP)
	printf "$(RED)$(FCLEAN_MESSAGE)$(RESET)\n"
endef

define clean_test
	$(RM) $(BUILD_DIR)
	$(SLEEP)
	printf "$(RED)$(CLEAN_MESSAGE)\n$(RESET)"
endef

define debug
	$(call clean)
	$(call fclean)
	$(MAKE) WITH_DEBUG=TRUE
endef

define comp_test
	$(CC) $(LDFLAGS) $(OBJS) $(OBJS_TEST) $(LDLIBS) -o $(NAME_TEST_PATH)
	-valgrind --leak-check=full \
                  -s \
                  --show-reachable=yes \
                  --errors-for-leak-kinds=all \
                  --track-origins=yes \
                  --track-fds=yes \./$(NAME_TEST_PATH)
endef

#******************************************************************************#
#                                   TARGETS                                    #
#******************************************************************************#

all: $(LIBFTX) $(MLX42) $(NAME_PATH)

$(BUILD_DIR)%.o: %.c
	$(call create_dir)
	$(call comp_objs)

$(NAME_PATH): $(OBJS) $(OBJS_MAIN)
	$(call comp_exe)

$(NAME_TEST_PATH): $(LIBFTX) $(MLX42) $(OBJS) $(OBJS_TEST)
	$(call comp_test)

$(LIBFTX):
	$(call submodule_update_libftx)

$(MLX42):
	$(call submodule_update_mlx42)

clean:
	$(call clean)

fclean: clean
	$(call fclean)

clean_test:
	$(call clean_test)

re: fclean all

debug:
	$(call debug)

test: clean_test $(NAME_TEST_PATH)

etags:
	etags $$(find . -name '*.[ch]')

.PHONY: all clean fclean clean_test re debug test etags
.DEFAULT_GOAL := all
.SILENT:

-include $(DEPS)
