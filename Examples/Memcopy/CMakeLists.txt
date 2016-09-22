INCLUDE_DIRECTORIES(${CAPI_INCLUDE_DIRS})
ADD_EXECUTABLE(host_memcopy host_memcopy.cpp)
TARGET_LINK_LIBRARIES(host_memcopy BlueLinkHost pthread ${CAPI_CXL_LIBRARY})

IF(USE_BLUESPEC)
  ADD_BSV_PACKAGE(Memcopy)
  ADD_DEPENDENCIES(Memcopy Core AFUShims)

  ADD_BLUESPEC_VERILOG_OUTPUT(Memcopy mkMemcopyAFU)
ENDIF()


IF(CAPI_SIM_FOUND)
  ## Post-build commands for CAPI simulation

  ADD_CUSTOM_COMMAND(TARGET verilog_mkMemcopyAFU POST_BUILD
    COMMAND xvlog mkMemcopyAFU.v
    COMMAND xvlog ${BLUESPEC_ROOT}/lib/Verilog/FIFO*.v
    COMMAND xvlog -d MODULENAME=mkMemcopyAFU -d HA_ASSIGNMENT_DELAY=${BLUELINK_HA_ASSIGNMENT_DELAY} --sv ${CMAKE_SOURCE_DIR}/PSLVerilog/afu_driver_top.v ${CMAKE_SOURCE_DIR}/PSLVerilog/revwrap.v
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} 
    )

  ADD_CUSTOM_TARGET(sim_Memcopy DEPENDS verilog_mkMemcopyAFU host_memcopy)
  ADD_CUSTOM_COMMAND(TARGET sim_Memcopy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/pslse.parms   ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/shim_host.dat ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/pslse_server.dat ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND xelab -timescale 1ns/1ps work.mkMemcopyAFU_pslse_top -sv_root ${CAPI_SIM_ROOT}/afu_driver/src -sv_lib libdpi -debug all 
    COMMAND xsim --runall work.mkMemcopyAFU_pslse_top
    )

ENDIF()
