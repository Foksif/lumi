{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  packages = with pkgs; [
  llvmPackages.libcxx

  cmake
  gnumake
  git
  ];
  nativeBuildInputs = with pkgs; [ nlohmann_json libnghttp2 pkg-config ];
  buildInputs = with pkgs; [ glib gtk4 libsoup_3 webkitgtk_6_0 libselinux libsepol fribidi libthai lerc xz zstd libwebp sqlite libpsl libdatrie expat libxdmcp libdeflate util-linux pcre2 libsysprof-capture gst_all_1.gstreamer gst_all_1.gst-plugins-base ];
  inputsFrom = with pkgs; [
    gtk4
    webkitgtk_6_0
  ];

  shellHook = ''
    export CC=clang
    export CXX=clang++

    export CPLUS_INCLUDE_PATH="${pkgs.llvmPackages.libcxx}/include/c++/v1"
    export NIX_CFLAGS_COMPILE="$(pkg-config --cflags --libs webkitgtk-6.0) $NIX_CFLAGS_COMPILE"
    unset NIX_LDFLAGS
  '';
}
