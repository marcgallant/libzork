set(CMAKE_CXX_STANDARD 20)

target_sources(libzork PRIVATE
               action.cc
               action_impl.cc
               condition.cc
               condition_impl.cc
               )
