project(my_project)
set(VAR1 "var1") # local variable
set(VAR2 "var2" CACHE STRING "Description1") # cached variable
set(VAR3 "var3" CACHE STRING "Description2" FORCE) # cached variable
option(OPT "This is an option" ON) # boolean cached variable
# same of var2
message(STATUS "${VAR1}, ${VAR2}, ${VAR3}, ${OPT}")

