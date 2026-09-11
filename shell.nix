{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  packages = with pkgs; [
  llvmPackages.libcxx

  cmake
  ninja
  pkg-config
  gnumake
  git

  gtk3
  webkitgtk_4_1

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
