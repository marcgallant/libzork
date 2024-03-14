set(CMAKE_CXX_STANDARD 20)

target_sources(libzork PRIVATE
               node.cc
               node_impl.cc
               story.cc
               story_impl.cc
               choice.cc
               )
