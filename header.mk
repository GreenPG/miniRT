define HEADER
██████████████████████████████████████████████████████
████                                              ████
███                                                ███
███                   \033[1;35m\e[1;46m▓▓▓▓▓▓▓▓▓▓▓▓\e[0m                 ███
██              \033[1;35m░░\e[1;46m████░░░░░░░░░░░░████\e[0m              ██
██            \033[1;35m░░\e[1;46m██▒▒░░░░░░░░░░░░░░░░░░██\e[0m            ██
██          \033[1;35m░░\e[1;46m██▒▒▒▒░░░░░░░░░░░░░░░░░░░░██\e[0m          ██
██         \033[1;35m\e[1;46m██▒▒▒▒░░░░░░░░░░░░░░    ░░░░░░██\e[0m         ██
██         \033[1;35m\e[1;46m██▒▒▒▒░░░░░░░░░░░░        ░░░░██\e[0m         ██
█        \033[1;35m\e[1;46m██▓▓▒▒▒▒░░░░░░░░░░░░        ░░░░░░██\e[0m        █
█        \033[1;35m\e[1;46m██▓▓▒▒▒▒░░░░░░░░░░░░░░    ░░░░░░░░██\e[0m        █
█        \033[1;35m\e[1;46m██▓▓▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░██\e[0m        █
█        \033[1;35m\e[1;46m██▓▓▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░██\e[0m        █
█        \033[1;35m\e[1;46m██▓▓▓▓▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░██\e[0m        █
█        \033[1;35m\e[1;46m██▓▓▓▓▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░██\e[0m        █
█          \033[1;35m\e[1;46m▓▓▓▓▓▓▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░██\e[0m          █
█          \033[1;35m\e[1;46m██▓▓▓▓▓▓▒▒▒▒▒▒▒▒░░░░░░░░░░▒▒▒▒██\e[0m          █
█          \033[1;35m░░\e[1;46m▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██\e[0m\033[1;35m░░ \e[0m         █
█            \033[1;35m░░\e[1;46m▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒██\e[0m\033[1;35m░░\e[0m            █
█              \033[1;35m░░\e[1;46m██▓▓▓▓▓▓▓▓▓▓▓▓▓▓████\e[0m\033[1;35m░░\e[0m              █
█                 \033[1;35m░░░░\e[1;46m████████████\e[0m\033[1;35m░░\e[0m                 █
█                     \033[1;35m░░░░░░░░░░░░\033[0m\e[0m                   █
█           \033[0;35m\e[5m__  __ _       _ _____ _______ \e[0m          █
██         \033[0;35m\e[5m|  \/  (_)     (_)  __ \__   __|\e[0m         ██
██         \033[0;35m\e[5m| \  / |_ _ __  _| |__) | | |\e[0m            ██
██         \033[0;35m\e[5m| |\/| | | '_ \| |  _  /  | |\e[0m            ██
██        \033[0;35m\e[5m | |  | | | | | | | | \ \  | |\e[0m            ██
██         \033[0;35m\e[5m|_|  |_|_|_| |_|_|_|  \_\ |_|\033[0m\e[0m            ██
███                                                ███
███                                                ███
████  With love by ❤️\e[0m \033[1;36m\e[4m\e]8;;https://github.com/GreenPG\aGpasquet\e]8;;\a\e[24m\033[0m❤️\e[0m  and ❤️\e[0m \e[38;5;201m\e[4m\e]8;;https://github.com/TheEmperorPenguin\aGtouzali\e]8;;\a\e[24m\033[0m❤️\e[0m   ████
██████████████████████████████████████████████████████
endef
export HEADER

header :
	@echo "$$HEADER"

.PHONY: header