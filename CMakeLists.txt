
set(krita_ctlbrush_PART_SRCS ctlbrush.cc ctlbrush_dock.cc kis_ctl_brush.cc )

kde4_add_ui_files(krita_ctlbrush_PART_SRCS CTLBrushEditor.ui )

kde4_add_plugin(kritactlbrush ${krita_ctlbrush_PART_SRCS})

target_link_libraries(kritactlbrush  ${KRITA_UI_LIBS} ${OPENCTL_LIBRARIES} ${KRITA_PAINTOP_LIBS})
set_target_properties( kritactlbrush PROPERTIES COMPILE_FLAGS ${OPENCTL_COMPILE_FLAGS})


install(TARGETS kritactlbrush  DESTINATION ${PLUGIN_INSTALL_DIR})


########### install files ###############

install( FILES  krita_ctlbrush.desktop  DESTINATION ${SERVICES_INSTALL_DIR})

