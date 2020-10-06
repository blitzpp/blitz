add_library(Meta INTERFACE)
add_library(Blitz::Meta ALIAS Meta)

install(FILES dot.h matassign.h matmat.h matvec.h metaprog.h product.h sum.h vecassign.h
        DESTINATION include/blitz/meta)
