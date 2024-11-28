import math

def calculate_pi(n_sides):
    radius = 1.0
    inner_perimeter = n_sides * 2.0 * radius * math.sin(math.pi / n_sides)
    outer_perimeter = n_sides * 2.0 * radius * math.tan(math.pi / n_sides)
    return inner_perimeter / (2.0 * radius), outer_perimeter / (2.0 * radius)

def main():
    n_sides = 3
    tolerance = 1e-15

    while True:
        pi_lower, pi_upper = calculate_pi(n_sides)
        if abs(pi_upper - pi_lower) < tolerance:
            print(f"Value of N is: {n_sides}")
            print(f"Estimated value of π is: {(pi_lower + pi_upper) / 2.0:.15f}")
            break
        n_sides += 1

if __name__ == "__main__":
    main()