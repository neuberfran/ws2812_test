# idf_component_register(
#     SRCS "ws2812.c" "main.c"
#     INCLUDE_DIRS "."
#     REQUIRES led_strip
# )

# idf_component_register(
#     SRCS
#         "main.c"
#         "ws2812.c"

#     INCLUDE_DIRS
#         "."

#     REQUIRES
#         led_strip
# )

# idf_component_register(
#     SRCS
#         "main.c"
#         "ws2812.c"

#     INCLUDE_DIRS
#         "."

#     REQUIRES
#         led_strip
# )

idf_component_register(
    SRCS
        "main.c"
        "ws2812.c"
        "effects.c"

    INCLUDE_DIRS
        "."

    REQUIRES
        led_strip
)