TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../dl_core.c

HEADERS += \
    ../include/dl_core.h \
    ../../php-src/usr/include/php/TSRM/readdir.h \
    ../../php-src/usr/include/php/TSRM/TSRM.h \
    ../../php-src/usr/include/php/TSRM/tsrm_config.h \
    ../../php-src/usr/include/php/TSRM/tsrm_config.w32.h \
    ../../php-src/usr/include/php/TSRM/tsrm_config_common.h \
    ../../php-src/usr/include/php/TSRM/tsrm_nw.h \
    ../../php-src/usr/include/php/TSRM/tsrm_strtok_r.h \
    ../../php-src/usr/include/php/TSRM/tsrm_win32.h \
    ../../php-src/usr/include/php/Zend/zend.h \
    ../../php-src/usr/include/php/Zend/zend_alloc.h \
    ../../php-src/usr/include/php/Zend/zend_API.h \
    ../../php-src/usr/include/php/Zend/zend_ast.h \
    ../../php-src/usr/include/php/Zend/zend_build.h \
    ../../php-src/usr/include/php/Zend/zend_builtin_functions.h \
    ../../php-src/usr/include/php/Zend/zend_closures.h \
    ../../php-src/usr/include/php/Zend/zend_compile.h \
    ../../php-src/usr/include/php/Zend/zend_config.h \
    ../../php-src/usr/include/php/Zend/zend_config.nw.h \
    ../../php-src/usr/include/php/Zend/zend_config.w32.h \
    ../../php-src/usr/include/php/Zend/zend_constants.h \
    ../../php-src/usr/include/php/Zend/zend_dtrace.h \
    ../../php-src/usr/include/php/Zend/zend_dynamic_array.h \
    ../../php-src/usr/include/php/Zend/zend_errors.h \
    ../../php-src/usr/include/php/Zend/zend_exceptions.h \
    ../../php-src/usr/include/php/Zend/zend_execute.h \
    ../../php-src/usr/include/php/Zend/zend_extensions.h \
    ../../php-src/usr/include/php/Zend/zend_float.h \
    ../../php-src/usr/include/php/Zend/zend_gc.h \
    ../../php-src/usr/include/php/Zend/zend_generators.h \
    ../../php-src/usr/include/php/Zend/zend_globals.h \
    ../../php-src/usr/include/php/Zend/zend_globals_macros.h \
    ../../php-src/usr/include/php/Zend/zend_hash.h \
    ../../php-src/usr/include/php/Zend/zend_highlight.h \
    ../../php-src/usr/include/php/Zend/zend_indent.h \
    ../../php-src/usr/include/php/Zend/zend_ini.h \
    ../../php-src/usr/include/php/Zend/zend_ini_parser.h \
    ../../php-src/usr/include/php/Zend/zend_ini_scanner.h \
    ../../php-src/usr/include/php/Zend/zend_ini_scanner_defs.h \
    ../../php-src/usr/include/php/Zend/zend_interfaces.h \
    ../../php-src/usr/include/php/Zend/zend_istdiostream.h \
    ../../php-src/usr/include/php/Zend/zend_iterators.h \
    ../../php-src/usr/include/php/Zend/zend_language_parser.h \
    ../../php-src/usr/include/php/Zend/zend_language_scanner.h \
    ../../php-src/usr/include/php/Zend/zend_language_scanner_defs.h \
    ../../php-src/usr/include/php/Zend/zend_list.h \
    ../../php-src/usr/include/php/Zend/zend_llist.h \
    ../../php-src/usr/include/php/Zend/zend_modules.h \
    ../../php-src/usr/include/php/Zend/zend_multibyte.h \
    ../../php-src/usr/include/php/Zend/zend_multiply.h \
    ../../php-src/usr/include/php/Zend/zend_object_handlers.h \
    ../../php-src/usr/include/php/Zend/zend_objects.h \
    ../../php-src/usr/include/php/Zend/zend_objects_API.h \
    ../../php-src/usr/include/php/Zend/zend_operators.h \
    ../../php-src/usr/include/php/Zend/zend_ptr_stack.h \
    ../../php-src/usr/include/php/Zend/zend_qsort.h \
    ../../php-src/usr/include/php/Zend/zend_signal.h \
    ../../php-src/usr/include/php/Zend/zend_stack.h \
    ../../php-src/usr/include/php/Zend/zend_static_allocator.h \
    ../../php-src/usr/include/php/Zend/zend_stream.h \
    ../../php-src/usr/include/php/Zend/zend_string.h \
    ../../php-src/usr/include/php/Zend/zend_strtod.h \
    ../../php-src/usr/include/php/Zend/zend_ts_hash.h \
    ../../php-src/usr/include/php/Zend/zend_types.h \
    ../../php-src/usr/include/php/Zend/zend_variables.h \
    ../../php-src/usr/include/php/Zend/zend_virtual_cwd.h \
    ../../php-src/usr/include/php/Zend/zend_vm.h \
    ../../php-src/usr/include/php/Zend/zend_vm_def.h \
    ../../php-src/usr/include/php/Zend/zend_vm_execute.h \
    ../../php-src/usr/include/php/Zend/zend_vm_opcodes.h \
    ../../php-src/usr/include/php/main/streams/php_stream_context.h \
    ../../php-src/usr/include/php/main/streams/php_stream_filter_api.h \
    ../../php-src/usr/include/php/main/streams/php_stream_glob_wrapper.h \
    ../../php-src/usr/include/php/main/streams/php_stream_mmap.h \
    ../../php-src/usr/include/php/main/streams/php_stream_plain_wrapper.h \
    ../../php-src/usr/include/php/main/streams/php_stream_transport.h \
    ../../php-src/usr/include/php/main/streams/php_stream_userspace.h \
    ../../php-src/usr/include/php/main/streams/php_streams_int.h \
    ../../php-src/usr/include/php/main/build-defs.h \
    ../../php-src/usr/include/php/main/fopen_wrappers.h \
    ../../php-src/usr/include/php/main/php.h \
    ../../php-src/usr/include/php/main/php_compat.h \
    ../../php-src/usr/include/php/main/php_config.h \
    ../../php-src/usr/include/php/main/php_content_types.h \
    ../../php-src/usr/include/php/main/php_getopt.h \
    ../../php-src/usr/include/php/main/php_globals.h \
    ../../php-src/usr/include/php/main/php_ini.h \
    ../../php-src/usr/include/php/main/php_main.h \
    ../../php-src/usr/include/php/main/php_memory_streams.h \
    ../../php-src/usr/include/php/main/php_network.h \
    ../../php-src/usr/include/php/main/php_open_temporary_file.h \
    ../../php-src/usr/include/php/main/php_output.h \
    ../../php-src/usr/include/php/main/php_reentrancy.h \
    ../../php-src/usr/include/php/main/php_scandir.h \
    ../../php-src/usr/include/php/main/php_stdint.h \
    ../../php-src/usr/include/php/main/php_streams.h \
    ../../php-src/usr/include/php/main/php_syslog.h \
    ../../php-src/usr/include/php/main/php_ticks.h \
    ../../php-src/usr/include/php/main/php_variables.h \
    ../../php-src/usr/include/php/main/php_version.h \
    ../../php-src/usr/include/php/main/rfc1867.h \
    ../../php-src/usr/include/php/main/SAPI.h \
    ../../php-src/usr/include/php/main/snprintf.h \
    ../../php-src/usr/include/php/main/spprintf.h \
    ../../php-src/usr/include/php/main/win32_internal_function_disabled.h \
    ../../php-src/usr/include/php/main/win95nt.h \
    ../../php-src/usr/include/php/ext/date/lib/timelib.h \
    ../../php-src/usr/include/php/ext/date/lib/timelib_config.h \
    ../../php-src/usr/include/php/ext/date/lib/timelib_structs.h \
    ../../php-src/usr/include/php/ext/date/php_date.h \
    ../../php-src/usr/include/php/ext/ereg/regex/cclass.h \
    ../../php-src/usr/include/php/ext/ereg/regex/cname.h \
    ../../php-src/usr/include/php/ext/ereg/regex/regex.h \
    ../../php-src/usr/include/php/ext/ereg/regex/regex2.h \
    ../../php-src/usr/include/php/ext/ereg/regex/utils.h \
    ../../php-src/usr/include/php/ext/ereg/php_ereg.h \
    ../../php-src/usr/include/php/ext/ereg/php_regex.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/mbfl/eaw_table.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/mbfl/mbfilter.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/mbfl/mbfilter_8bit.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/mbfl/mbfilter_pass.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/mbfl/mbfilter_wchar.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/mbfl/mbfl_allocators.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/mbfl/mbfl_consts.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/mbfl/mbfl_convert.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/mbfl/mbfl_defs.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/mbfl/mbfl_encoding.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/mbfl/mbfl_filter_output.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/mbfl/mbfl_ident.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/mbfl/mbfl_language.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/mbfl/mbfl_memory_device.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/mbfl/mbfl_string.h \
    ../../php-src/usr/include/php/ext/mbstring/libmbfl/config.h \
    ../../php-src/usr/include/php/ext/mbstring/oniguruma/oniguruma.h \
    ../../php-src/usr/include/php/ext/mbstring/mbstring.h \
    ../../php-src/usr/include/php/ext/mbstring/php_mbregex.h \
    ../../php-src/usr/include/php/ext/mbstring/php_onig_compat.h \
    ../../php-src/usr/include/php/ext/pcre/pcrelib/config.h \
    ../../php-src/usr/include/php/ext/pcre/pcrelib/pcre.h \
    ../../php-src/usr/include/php/ext/pcre/pcrelib/pcre_internal.h \
    ../../php-src/usr/include/php/ext/pcre/pcrelib/pcreposix.h \
    ../../php-src/usr/include/php/ext/pcre/pcrelib/ucp.h \
    ../../php-src/usr/include/php/ext/pcre/php_pcre.h \
    ../../php-src/usr/include/php/ext/spl/php_spl.h \
    ../../php-src/usr/include/php/ext/spl/spl_array.h \
    ../../php-src/usr/include/php/ext/spl/spl_directory.h \
    ../../php-src/usr/include/php/ext/spl/spl_dllist.h \
    ../../php-src/usr/include/php/ext/spl/spl_engine.h \
    ../../php-src/usr/include/php/ext/spl/spl_exceptions.h \
    ../../php-src/usr/include/php/ext/spl/spl_fixedarray.h \
    ../../php-src/usr/include/php/ext/spl/spl_functions.h \
    ../../php-src/usr/include/php/ext/spl/spl_heap.h \
    ../../php-src/usr/include/php/ext/spl/spl_iterators.h \
    ../../php-src/usr/include/php/ext/spl/spl_observer.h \
    ../../php-src/usr/include/php/ext/standard/base64.h \
    ../../php-src/usr/include/php/ext/standard/basic_functions.h \
    ../../php-src/usr/include/php/ext/standard/crc32.h \
    ../../php-src/usr/include/php/ext/standard/credits.h \
    ../../php-src/usr/include/php/ext/standard/credits_ext.h \
    ../../php-src/usr/include/php/ext/standard/credits_sapi.h \
    ../../php-src/usr/include/php/ext/standard/crypt_blowfish.h \
    ../../php-src/usr/include/php/ext/standard/crypt_freesec.h \
    ../../php-src/usr/include/php/ext/standard/css.h \
    ../../php-src/usr/include/php/ext/standard/cyr_convert.h \
    ../../php-src/usr/include/php/ext/standard/datetime.h \
    ../../php-src/usr/include/php/ext/standard/dl.h \
    ../../php-src/usr/include/php/ext/standard/exec.h \
    ../../php-src/usr/include/php/ext/standard/file.h \
    ../../php-src/usr/include/php/ext/standard/flock_compat.h \
    ../../php-src/usr/include/php/ext/standard/fsock.h \
    ../../php-src/usr/include/php/ext/standard/head.h \
    ../../php-src/usr/include/php/ext/standard/html.h \
    ../../php-src/usr/include/php/ext/standard/html_tables.h \
    ../../php-src/usr/include/php/ext/standard/info.h \
    ../../php-src/usr/include/php/ext/standard/md5.h \
    ../../php-src/usr/include/php/ext/standard/microtime.h \
    ../../php-src/usr/include/php/ext/standard/pack.h \
    ../../php-src/usr/include/php/ext/standard/pageinfo.h \
    ../../php-src/usr/include/php/ext/standard/php_array.h \
    ../../php-src/usr/include/php/ext/standard/php_assert.h \
    ../../php-src/usr/include/php/ext/standard/php_browscap.h \
    ../../php-src/usr/include/php/ext/standard/php_crypt.h \
    ../../php-src/usr/include/php/ext/standard/php_crypt_r.h \
    ../../php-src/usr/include/php/ext/standard/php_dir.h \
    ../../php-src/usr/include/php/ext/standard/php_dns.h \
    ../../php-src/usr/include/php/ext/standard/php_ext_syslog.h \
    ../../php-src/usr/include/php/ext/standard/php_filestat.h \
    ../../php-src/usr/include/php/ext/standard/php_fopen_wrappers.h \
    ../../php-src/usr/include/php/ext/standard/php_ftok.h \
    ../../php-src/usr/include/php/ext/standard/php_http.h \
    ../../php-src/usr/include/php/ext/standard/php_image.h \
    ../../php-src/usr/include/php/ext/standard/php_incomplete_class.h \
    ../../php-src/usr/include/php/ext/standard/php_iptc.h \
    ../../php-src/usr/include/php/ext/standard/php_lcg.h \
    ../../php-src/usr/include/php/ext/standard/php_link.h \
    ../../php-src/usr/include/php/ext/standard/php_mail.h \
    ../../php-src/usr/include/php/ext/standard/php_math.h \
    ../../php-src/usr/include/php/ext/standard/php_metaphone.h \
    ../../php-src/usr/include/php/ext/standard/php_password.h \
    ../../php-src/usr/include/php/ext/standard/php_rand.h \
    ../../php-src/usr/include/php/ext/standard/php_smart_str.h \
    ../../php-src/usr/include/php/ext/standard/php_smart_str_public.h \
    ../../php-src/usr/include/php/ext/standard/php_standard.h \
    ../../php-src/usr/include/php/ext/standard/php_string.h \
    ../../php-src/usr/include/php/ext/standard/php_type.h \
    ../../php-src/usr/include/php/ext/standard/php_uuencode.h \
    ../../php-src/usr/include/php/ext/standard/php_var.h \
    ../../php-src/usr/include/php/ext/standard/php_versioning.h \
    ../../php-src/usr/include/php/ext/standard/proc_open.h \
    ../../php-src/usr/include/php/ext/standard/quot_print.h \
    ../../php-src/usr/include/php/ext/standard/scanf.h \
    ../../php-src/usr/include/php/ext/standard/sha1.h \
    ../../php-src/usr/include/php/ext/standard/streamsfuncs.h \
    ../../php-src/usr/include/php/ext/standard/uniqid.h \
    ../../php-src/usr/include/php/ext/standard/url.h \
    ../../php-src/usr/include/php/ext/standard/url_scanner_ex.h \
    ../../php-src/usr/include/php/ext/standard/winver.h

DISTFILES += \
    ../test.php \
    ../rows.php

