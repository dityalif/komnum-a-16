import pandas as pd
import numpy as np
from scipy.interpolate import interp1d

# Fungsi untuk menampilkan hasil interpolasi
def print_interpolasi(estimated_population, estimated_internet_users):
    print("=== Estimasi Populasi dan Pengguna Internet untuk Tahun yang Hilang ===")
    print("Populasi (dalam jiwa):")
    for year, pop in estimated_population.items():
        print(f"  Tahun {year}: {pop:,.0f}")
    print("\nPersentase Pengguna Internet (%):")
    for year, users in estimated_internet_users.items():
        print(f"  Tahun {year}: {users:.4f}%")

# Fungsi untuk menampilkan persamaan polinomial
def print_persamaan(population_eq, internet_users_eq):
    print("\n=== Persamaan Polinomial ===")
    print("Persamaan untuk Populasi:")
    print(f"  {population_eq}")
    print("Persamaan untuk Pengguna Internet:")
    print(f"  {internet_users_eq}")

# Fungsi untuk menampilkan estimasi masa depan
def print_estimasi(population_2030, internet_users_2035):
    print("\n=== Estimasi Masa Depan ===")
    print(f"Populasi Indonesia di tahun 2030: {population_2030:,.0f} jiwa")
    print(f"Pengguna Internet di Indonesia di tahun 2035: {internet_users_2035:.4f}%\n")

# Baca data dari file CSV
data = pd.read_csv("d:/Akademis/Teknik Komputer/Semester 4/Komnum/Data Tugas Pemrograman A.csv")

# Ambil kolom tahun, populasi, dan persentase pengguna Internet
years = data['Year']
population = data['Population']
internet_users = data['Percentage_Internet_User']

# Interpolasi untuk tahun yang hilang
missing_years = [2005, 2006, 2015, 2016]
interp_population = interp1d(years, population, kind='linear', fill_value="extrapolate")
interp_internet_users = interp1d(years, internet_users, kind='linear', fill_value="extrapolate")

# Hitung nilai interpolasi
estimated_population = {year: interp_population(year) for year in missing_years}
estimated_internet_users = {year: interp_internet_users(year) for year in missing_years}

# Regresi polinomial untuk populasi dan pengguna Internet
poly_population = np.polyfit(years, population, 3)  # Polinomial orde 3
poly_internet_users = np.polyfit(years, internet_users, 3)

# Formulasikan persamaan polinomial
population_eq = f"y = {poly_population[0]:.2f}x^3 + {poly_population[1]:.2f}x^2 + {poly_population[2]:.2f}x + {poly_population[3]:.2f}"
internet_users_eq = f"y = {poly_internet_users[0]:.2f}x^3 + {poly_internet_users[1]:.2f}x^2 + {poly_internet_users[2]:.2f}x + {poly_internet_users[3]:.2f}"

# Estimasi populasi tahun 2030 dan pengguna Internet tahun 2035
population_2030 = np.polyval(poly_population, 2030)
internet_users_2035 = np.polyval(poly_internet_users, 2035)

# Tampilkan hasil
print_interpolasi(estimated_population, estimated_internet_users)
print_persamaan(population_eq, internet_users_eq)
print_estimasi(population_2030, internet_users_2035)