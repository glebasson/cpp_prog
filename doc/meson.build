doxyfile = configuration_data()
doxyfile.set('OUTPUT_DIRECTORY', meson.build_root() + '/doc')
doxyfile.set('INPUT', meson.source_root() + '/src/component_programming')
configure_file(input:'Doxyfile.in', output:'Doxyfile', configuration: doxyfile)

doxygen = find_program('doxygen')
if doxygen.found()
    run_target('doc', command: 'doxygen ' + meson.build_root() + '/doc/Doxyfile')
    # [doxygen, meson.build_root() + '/doc/Doxyfile']
endif