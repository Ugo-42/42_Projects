# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    used_func.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 10:27:31 by ugwentzi          #+#    #+#              #
#    Updated: 2025/08/20 11:30:18 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .makefile.conf/color.mk

GOLD := \033[1;38;2;147;117;42m

AUTHORIZED_FUNC = \
	open close read write printf malloc free \
	perror strerror exit gettimeofday \

# lib maths
AUTHORIZED_FUNC += \
	abs acos acosf acosh acoshf asin asinf asinh asinhf atan atanf atanh \
	atanhf atan2 atan2f cbrt cbrtf ceil ceilf copysign copysignf cos cosf cosh \
	coshf exp expf exp2 exp2f expm1 expm1f fabs fabsf fdim fdimf floor floorf \
	fma fmaf fmax fmaxf fmin fminf fmod fmodf frexp frexpf hypot hypotf ilogb \
	ilogbf ldexp ldexpf lgamma lgammaf llrint llrintf llround llroundf log \
	logf log10 log10f log1p log1pf log2 log2f logb logbf modf modff nanf \
	nearbyint nearbyintf nextafter nextafterf nexttoward nexttowardf pow powf \
	remainder remainderf remquo remquof rint rintf round roundf scalbln \
	scalblnf scalbn scalbnf sin sinf sinh sinhf sqrt sqrtf tan tanf tanh tanhf \
	tgamma tgammaf trunc truncf

# lib mlx
IGNORED_FUNC = \
	calloc dlclose dlopen dlsym fclose fgets fopen fputs fread fseek ftell \
	fwrite fprintf glfwCreateWindow glfwFocusWindow glfwGetPrimaryMonitor \
	glfwGetProcAddress glfwGetMonitors glfwGetKey glfwGetTime glfwGetWindowPos \
	glfwGetWindowSize glfwGetWindowUserPointer glfwInit glfwMakeContextCurrent \
	glfwPollEvents glfwSetFramebufferSizeCallback glfwSetKeyCallback \
	glfwSetWindowCloseCallback glfwSetWindowIcon glfwSetWindowPos glfwGetVideoMode \
	glfwSetWindowShouldClose glfwSetWindowSize glfwSetWindowSizeCallback \
	glfwSetWindowSizeLimits glfwSetWindowTitle glfwSetWindowUserPointer \
	glfwSwapBuffers glfwSwapInterval glfwTerminate glfwWindowHint \
	glfwGetCursorPos glfwGetMouseButton glfwSetCursorPos glfwSetCursorPosCallback \
	glfwSetMouseButtonCallback glfwSetScrollCallback glfwWindowShouldClose \
	glfwCreateCursor glfwCreateStandardCursor glfwDestroyCursor glfwSetCursor \
	glfwSetInputMode memcpy memmove memset realloc stderr strlen strncat strncmp \
	strrchr

IGNORED_MSG := (mlx42)

used_func:
	@printf "$(GOLD)External Functions:$(RESET)\n"
	@nm -u ./$(NAME) | awk '/^[[:space:]]*U /{print $$2}' | sed 's/@.*//' | \
		sort -u | grep -v '^__' | \
	( \
		suppressed=0; \
		while read func; do \
			auth=0; ignore=0; \
			for allowed in $(AUTHORIZED_FUNC); do \
				[ "$$func" = "$$allowed" ] && auth=1 && break; \
			done; \
			for skipped in $(IGNORED_FUNC); do \
				[ "$$func" = "$$skipped" ] && ignore=1 && break; \
			done; \
			if [ $$auth -eq 1 ]; then \
				printf " $(GOLD)│$(RESET)   — $(GREEN)%s$(RESET)\n" "$$func"; \
			elif [ $$ignore -eq 1 ]; then \
				suppressed=$$((suppressed + 1)); \
			else \
				printf " $(GOLD)│$(RESET)   — $(RED)%s$(RESET)\n" "$$func"; \
			fi; \
		done; \
		if [ $$suppressed -gt 0 ]; then \
			printf " $(GOLD)#$(RESET)   $(ITALIC)%d functions suppressed %s$(RESET)\n" \
				"$$suppressed" "$(IGNORED_MSG)"; \
		fi \
	)

.PHONY: used_func
