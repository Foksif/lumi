{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  packages = with pkgs; [
    clang
    cmake
    ninja
    pkg-config
    gnumake
    git

    gtk3
    webkitgtk_4_1
    sysprof
  ];
}
