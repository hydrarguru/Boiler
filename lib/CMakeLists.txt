include(FetchContent)

FetchContent_Declare(
  sfml
  GIT_REPOSITORY "https://github.com/SFML/SFML"
  GIT_TAG 2f11710abc5aa478503a7ff3f9e654bd2078ebab # 2.5.1
)

add_subdirectory(sfml)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  #GIT_TAG 35b1148efb839381b84de9290d9caf0b66ad7d03
  GIT_TAG 377b864bb4a9ed9a25674b04f64f63baf221060d #imgui-docking
)

FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY "https://github.com/eliasdaler/imgui-sfml"
  #GIT_TAG 82dc2033e51b8323857c3ae1cf1f458b3a933c35 # 2.3
  GIT_TAG 15753d56403a7aeb1cae12fd930cfb1d2eac5e74 # 2.5
)
add_subdirectory(imgui-sfml)
