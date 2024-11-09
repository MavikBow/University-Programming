! we work with the equation f(x) = (1 - x**5) / 3
!
! n is the number of iterations

program AlEq
    implicit none

    integer, parameter :: dp = selected_real_kind(15, 307)
    real(kind=dp) :: x0, x1, radius, alpha, n_calculated, lambda_0
    real(kind=dp), parameter :: Eps = 0.0001_dp
    integer :: n_approximated, n_actual 

    radius = 0.5_dp

    alpha = (5.0_dp / 3.0_dp) * radius**4

    print '(A)', 'the contraction coefficient alpha'       
    print '(F14.5)', alpha 

    x0 = 0.0_dp
    x1 = (1.0_dp - x0**5) / 3.0_dp

    n_calculated = log(((1.0_dp - alpha) * Eps)/abs(x0 - x1)) / log(alpha)
    print '(A)', 'the calculated number of iterations'       
    print '(F14.5)', n_calculated

    n_approximated = int(n_calculated) + 1
    print '(A)', 'the approximate number of iterations' 
    print *, n_approximated

    n_actual = 0
    do 
        x1 = (1.0_dp - x0**5) / 3.0_dp
        n_actual = n_actual + 1
        if (abs(x0-x1) < Eps) exit
        x0 = x1
    end do

    print '(A)', 'the actual number of iterations'
    print *, n_actual

    print '(A)', 'the last iteration'
    print '(F14.5)', x1

end program AlEq
