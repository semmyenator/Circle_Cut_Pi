// This function calculates the lower and upper estimates of π
// based on the number of sides of a polygon inscribed in a circle.
fn calculate_pi(n_sides: usize) -> (f64, f64) {
    let radius = 1.0; // The radius of the circle is set to 1.0
    let angle = 2.0 * (0.0_f64).acos(); // Calculate 2 * arccos(0), which equals π

    // Calculate the inner perimeter using the sine function
    let inner_perimeter = n_sides as f64 * 2.0 * radius * (angle / n_sides as f64).sin();
    
    // Calculate the outer perimeter using the tangent function
    let outer_perimeter = n_sides as f64 * 2.0 * radius * (angle / n_sides as f64).tan();
    
    // Return the estimates of π based on the inner and outer perimeters
    // divided by the diameter (2 * radius).
    (inner_perimeter / (2.0 * radius), outer_perimeter / (2.0 * radius))
}

fn main() {
    let mut n_sides: usize = 3; // Start with a triangle (3 sides)
    const TOLERANCE: f64 = 1e-15; // Set the tolerance for the estimation precision
    
    loop {
        // Calculate the lower and upper estimates of π
        let (pi_lower, pi_upper) = calculate_pi(n_sides);
        
        // Check if the difference between upper and lower estimates is within the tolerance
        if (pi_upper - pi_lower).abs() < TOLERANCE {
            // Print the number of sides used and the estimated value of π
            println!("Value of N is: {}", n_sides);
            println!("Estimated value of π is: {:.15}", (pi_lower + pi_upper) / 2.0);
            break; // Exit the loop once the estimation is precise enough
        }
        
        n_sides += 1; // Increase the number of sides for a more accurate estimation
    }
}
