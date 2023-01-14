cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project("txtlib"
        VERSION 0.1.0
        DESCRIPTION "A library for the robotics txt controller"
        LANGUAGES CXX
)

add_subdirectory(txtlib)
add_subdirectory(example)

set(RESULT_BINARY ${txtapp_BINARY_DIR}/txtapp)

if(NOT DEFINED TXT_IP)
set(TXT_IP "192.168.7.2")
endif()

add_custom_target(upload COMMAND scp ${RESULT_BINARY} ROBOPro@${TXT_IP}:/opt/knobloch/C-Program/ USES_TERMINAL)
add_custom_target(run COMMAND ssh ROBOPro@${TXT_IP} /opt/knobloch/C-Program/txtapp USES_TERMINAL)