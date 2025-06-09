import folium

coords = [
    (11.103115, 106.6127489),
    (11.1056994, 106.6115562),
    (11.1030523, 106.6127396),
    (11.1031216, 106.6127577),
    (11.1030979, 106.6127644),
    (11.1030787, 106.6127467),
    (11.1031085, 106.6127483)
]

m = folium.Map(location=coords[0], zoom_start=17)
folium.PolyLine(coords, color="blue", weight=5).add_to(m)

for i, (lat, lon) in enumerate(coords):
    folium.Marker([lat, lon], tooltip=f"Point {i+1}").add_to(m)

m.save("gps_path_map.html")
