# === CONFIGURATION ===
NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I includes/ -g3

# === COULEURS ===
RESET       = \033[0m
GREEN       = \033[32m
RED         = \033[31m
YELLOW      = \033[33m

# === RÉPERTOIRES ===
SRC_DIR     = src/
OBJ_DIR     = obj/
OCTOLIB_DIR = octolib
OCTOLIB_A   = $(OCTOLIB_DIR)/libft.a

# === SOURCES ===
SRC         = src/find_cmd_path.c\
			  src/ft_cd.c\
			  src/ft_strjoin_three.c\
			  src/ft_echo.c\
			  src/ft_env.c\
			  src/ft_exec.c\
			  src/ft_exec_1.c\
   			  src/ft_exec_utils_1.c\
			  src/ft_executables.c\
			  src/ft_exit.c\
			  src/ft_export_utils_1.c\
			  src/ft_export.c\
			  src/ft_here_doc.c\
			  src/ft_lexer_utils_1.c\
			  src/ft_lexer_utils_2.c\
			  src/ft_lexer.c\
			  src/ft_parce_util_1.c\
			  src/ft_parce_util.c\
			  src/ft_parse_1.c\
			  src/ft_parse.c\
			  src/ft_pipe_error.c\
			  src/ft_pipe_utils_1.c\
			  src/ft_pipe_utils.c\
			  src/ft_pipe_1.c\
			  src/ft_pipe.c\
			  src/ft_pwd.c\
			  src/ft_quote_utils_1.c\
			  src/ft_quote.c\
			  src/main.c\
			  src/signal.c\
			  src/tranform_in_tab.c\
			  src/unset.c\

OBJ         = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

# === PROGRESS BAR ===
TOTAL_FILES = $(words $(SRC))
COMPILED    = 0

define update_prupdateSources:
	@bash -c '\
		IGNORED_DIRS=("build" "test"); \
		FIND_CMD="find -type f -name '\''*.c'\''"; \
		for dir in "$${IGNORED_DIRS[@]}"; do \
			FIND_CMD+=" ! -path './\''$$dir/*'\''"; \
		done; \
		eval $$FIND_CMD | sort | awk '\''{print "\t" $$0 " \\"}'\'' \
		| sed '\''$$ s/ \\$$//'\'' > .sources_block; \
		cat .sources_block; \
		echo "SOURCES = \\" > .sources_full; \
		cat .sources_block >> .sources_full; \
		awk '\'' \
			FNR==NR { lines[NR] = $$0; next } \
			/^SOURCES =/ { \
				for (i=1; i<=length(lines); i++) print lines[i]; \
				in_block=1; next \
			} \
			in_block && /^[^\t]/ { in_block=0 } \
			!in_block { print } \
		'\'' .sources_full Makefile > Makefile.tmp; \
		mv Makefile.tmp Makefile; \
		rm -f .sources_block .sources_full; \
		echo ":coche_blanche: Makefile mis à jour avec les fichiers sources." \
	'ogress
	@$(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
	@printf "\r$(RED)Compiling [%-50s] %d%% (%d/%d)$(RESET)" \
		"$$(printf '█%.0s' $$(seq 1 $$(($(COMPILED)*50/$(TOTAL_FILES)))))" \
		$$(($(COMPILED)*100/$(TOTAL_FILES))) \
		$(COMPILED) \
		$(TOTAL_FILES)
endef

# === RÈGLES ===

all: $(NAME)

$(NAME): $(OBJ) | $(OCTOLIB_A)
	@$(CC) $(CFLAGS) $(OBJ) $(OCTOLIB_A) -o $(NAME) -lreadline
	@echo "\n$(RESET)✅ Compilation terminée : $(NAME)$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(update_progress)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OCTOLIB_A):
	@$(MAKE) -sC $(OCTOLIB_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -sC $(OCTOLIB_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -sC $(OCTOLIB_DIR) fclean

re: fclean all

updateSources:
	@bash -c '\
		# Répertoires à ignorer (ex : build, test, obj) \
		IGNORED_DIRS=("build" "test" "obj"); \
		# Répertoires à inclure (ajuste selon ta structure) \
		ALLOWED_SRC_DIRS=("src" "src/parser" "src/exec" "src/builtin" "src/redir" "src/utils"); \
		FIND_CMD=""; \
		for src_dir in "$${ALLOWED_SRC_DIRS[@]}"; do \
			FIND_CMD+="find $$src_dir -type f -name '\''*.c'\'' -o "; \
		done; \
		FIND_CMD=$${FIND_CMD% -o }; \
		for dir in "$${IGNORED_DIRS[@]}"; do \
			FIND_CMD+=" ! -path './$$dir/*'"; \
		done; \
		eval $$FIND_CMD | sort | awk '\''{print "\t" $$0 " \\"}'\'' \
		| sed '\''$$ s/ \\$$//'\'' > .sources_block; \
		cat .sources_block; \
		echo "SOURCES = \\" > .sources_full; \
		cat .sources_block >> .sources_full; \
		awk '\'' \
			FNR==NR { lines[NR] = $$0; next } \
			/^SOURCES =/ { \
				for (i=1; i<=length(lines); i++) print lines[i]; \
				in_block=1; next \
			} \
			in_block && /^[^\t]/ { in_block=0 } \
			!in_block { print } \
		'\'' .sources_full Makefile > Makefile.tmp; \
		mv Makefile.tmp Makefile; \
		rm -f .sources_block .sources_full; \
		echo "✅ Makefile mis à jour avec les fichiers sources." \
	'
	
.PHONY: all clean fclean re
