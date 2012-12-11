FILE(REMOVE_RECURSE
  "CMakeFiles/rebuild"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/rebuild.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
