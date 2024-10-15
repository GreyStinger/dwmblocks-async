{
  description = "Flake for dwmblocks";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
  };

  outputs = { self, nixpkgs }:
  let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in
  {
      # packages.${system}.default = import ./default.nix {
      #   pkgs = import nixpkgs { system = "x86_64-linux"; };
      # };

    devShells.${system}.default = pkgs.mkShell rec {
      hardeningDisable = [ "fortify" ];
      packages = [
        pkgs.libpkgconf
        pkgs.pkg-config
        pkgs.ccls
        pkgs.git
        pkgs.vim
      ];

      buildInputs = [
          # (import ./default.nix {
          #   pkgs = import nixpkgs { inherit system; };
          # })
        pkgs.xorg.libxcb
        pkgs.xorg.libX11
        pkgs.xorg.libXft
        pkgs.xorg.xcbutil
        pkgs.xorg.xcbutilkeysyms
        pkgs.xorg.xcbutilwm
      ];

      shellHook = ''
        export PKG_CONFIG_PATH="${pkgs.xorg.libxcb.dev}/lib/pkgconfig:${pkgs.xorg.libX11.dev}/lib/pkgconfig:${pkgs.xorg.libXft.dev}/lib/pkgconfig:${pkgs.xorg.xcbutil.dev}/lib/pkgconfig:${pkgs.xorg.xcbutilkeysyms.dev}/lib/pkgconfig:${pkgs.xorg.xcbutilwm.dev}/lib/pkgconfig"
        '';
    };

    packages.${system}.default = pkgs.callPackage ./default.nix {};
  };
}

