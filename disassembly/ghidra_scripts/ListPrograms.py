# Print each opened program's name, pathname, language, and image base.
# Run read-only with -process to enumerate programs in the project.
# @category Analysis
p = currentProgram
print("PROG name=%s path=%s lang=%s base=%s" % (
    p.getName(),
    p.getDomainFile().getPathname(),
    p.getLanguageID(),
    p.getImageBase()))
