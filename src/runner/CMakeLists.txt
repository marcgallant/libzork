set(CMAKE_CXX_STANDARD 20)

target_sources(libzork PRIVATE
               choice.cc
               choice_impl.cc
               html.cc
               html_impl.cc
               interactive.cc
               runner.cc
               smart.cc
               smart_impl.cc
               )
