#!/bin/bash
# Skrip pengaturan XFCE: memasang tema GTK gelap, ikon modern, font, picom, terminal, wallpaper, panel minimal,
# dan shortcut keyboard. Semua dilakukan otomatis via pacman dan xfconf-query:contentReference[oaicite:3]{index=3}:contentReference[oaicite:4]{index=4}.

# Perbarui sistem dan pasang paket penting (XFCE, picom, tema, ikon, browser, file manager, tools)
sudo pacman -Syu --noconfirm
sudo pacman -S --noconfirm xfce4 xfce4-goodies xfce4-terminal xfce4-settings \
    picom papirus-icon-theme arc-gtk-theme firefox thunar curl wget git \
    ttf-roboto noto-fonts ttf-dejavu ttf-liberation

# Aktifkan compositor picom dengan konfigurasi ringan (transparansi moderat, tanpa bayangan berat)
mkdir -p ~/.config/picom
cat > ~/.config/picom.conf <<EOF
backend = "glx";
vsync = true;
shadow = false;
fading = false;
inactive-opacity = 0.85;
active-opacity = 1.0;
EOF

# Atur tema GTK dan window manager ke varian gelap (Arc-Dark); atur ikon ke Papirus-Dark
xfconf-query -c xsettings -p /Net/ThemeName       -s "Arc-Dark"
xfconf-query -c xsettings -p /Net/IconThemeName   -s "Papirus-Dark"
xfconf-query -c xfwm4     -p /general/theme       -s "Arc-Dark"

# Atur font sistem agar halus dan mudah dibaca (misal Noto Sans dan Liberation)
xfconf-query -c xsettings -p /Gtk/FontName         -s "Noto Sans Regular 10"
xfconf-query -c xsettings -p /Gtk/CursorThemeName  -s "Adwaita"
xfconf-query -c xsettings -p /Xft/DPI              -s 96

# Konfigurasi xfce4-terminal agar sesuai tema gelap
# Nonaktifkan skema warna tema terminal, atur warna latar belakang gelap dan teks terang
xfconf-query -c xfce4-terminal -p /colors/use-theme-colors        -s false
xfconf-query -c xfce4-terminal -p /colors/use-theme-transparency  -s false
xfconf-query -c xfce4-terminal -p /colors/background-color        -s "#2e3440"
xfconf-query -c xfce4-terminal -p /colors/foreground-color        -s "#d8dee9"
xfconf-query -c xfce4-terminal -p /appearance/font-name           -s "Noto Sans Mono 11"

# Pasang wallpaper gelap default (download dari Unsplash) dan atur sebagai latar XFCE:contentReference[oaicite:5]{index=5}
sudo mkdir -p /usr/share/backgrounds/xfce
sudo curl -L -o /usr/share/backgrounds/xfce/xfce_dark_wallpaper.png "https://source.unsplash.com/1920x1080/?dark,abstract"
xfconf-query -c xfce4-desktop -p /backdrop/screen0/monitor0/workspace0/last-image \
    -s "/usr/share/backgrounds/xfce/xfce_dark_wallpaper.png"

# Konfigurasi panel XFCE minimalis dan simetris
# (posisi atas, lebar penuh, nonaktifkan autohide)
xfconf-query -c xfce4-panel -p /panels/panel-0/length             -s 100
xfconf-query -c xfce4-panel -p /panels/panel-0/autohide-behavior -s 0

# Shortcut keyboard produktif: Tambah Ctrl+Alt+T untuk terminal, Ctrl+Alt+B untuk browser, Ctrl+Alt+F untuk file manager:contentReference[oaicite:6]{index=6}
xfconf-query -c xfce4-keyboard-shortcuts -n -t string -p "/commands/custom/<Primary><Alt>t" -s "xfce4-terminal"
xfconf-query -c xfce4-keyboard-shortcuts -n -t string -p "/commands/custom/<Primary><Alt>b" -s "firefox"
xfconf-query -c xfce4-keyboard-shortcuts -n -t string -p "/commands/custom/<Primary><Alt>f" -s "thunar"

echo "Konfigurasi XFCE selesai. Silakan keluar dan masuk kembali (atau restart xfce4-session) untuk melihat perubahan."
