{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  packages = with pkgs; [
  llvmPackages.libcxx

  cmake
  pkg-config
  gnumake
  git

  gtk4
  webkitgtk_6_0
  libsoup_3

  gst_all_1.gstreamer
  gst_all_1.gst-plugins-base

  sysprof
];

  shellHook = ''
    export CC=clang
    export CXX=clang++

    export CPLUS_INCLUDE_PATH="${pkgs.llvmPackages.libcxx}/include/c++/v1"
  '';
}
