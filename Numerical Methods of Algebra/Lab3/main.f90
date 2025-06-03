program lab3
    implicit none
    double precision, parameter :: EPS = 1.0e-5
    double precision :: temp, exact_integral, M_2, M_4, M_6
    integer :: N_, N_T, N_C

    exact_integral = asin(sqrt(30.D0)/10.D0)**2 - asin(sqrt(5.D0)/5.D0)**2
    print '(F14.11)', exact_integral
    print *, ' '

    ! LP
    N_ = 4
    do 
        temp = abs(I_h(0.2D0, 0.3D0, N_/2) - I_h(0.2D0, 0.3D0, N_))
        if(temp < EPS) exit
        N_ = N_ * 2
    enddo

    print '(A)', "Left Rectangle"
    print '(A, I11)', 'opt_n= ', N_
    print '(A, ES11.4)', 'opt_h= ', 0.1D0 / dble(N_)
    print '(A, F14.11)', 'Integral= ', I_h(0.2D0, 0.3D0, N_)
    print '(A, ES11.4)', 'discrep= ', abs(I_h(0.2D0, 0.3D0, N_) - exact_integral)
    print *, ' '


    ! Trapezoidal
    M_2 = 2.66236D0
    N_T = ceiling(sqrt((M_2 * 0.001) / (12.D0 * EPS)))

    print '(A)', "Trapezoidal"
    print '(A, I11)', 'opt_n= ', N_T
    print '(A, ES11.4)', 'opt_h= ', 0.1D0 / dble(N_T)
    print '(A, F14.11)', 'Integral= ', I_T(0.2D0, 0.3D0, N_T)
    print '(A, ES11.4)', 'discrep= ', abs(I_T(0.2D0, 0.3D0, N_T) - exact_integral)
    print *, ' '

    ! Simpson
    M_4 = 49.2475D0
    N_C = ceiling(sqrt(sqrt((M_4 * 0.00001) / (180.D0 * EPS))))
!   N_C = ceiling(sqrt(sqrt((M_4 * 0.00001) / (180.D0 * 1e-14))))

    if(N_C .EQ. 1) then
        temp = I_C_2(0.2D0, 0.3D0, M_4)
    else
        N_C = N_C + mod(N_C,2)
        temp = I_C(0.2D0, 0.3D0, N_C)
    endif

    print '(A)', "Simpson"
    print '(A, I11)', 'opt_n= ', N_C
    print '(A, ES11.4)', 'opt_h= ', 0.1D0 / dble(N_C)
    print '(A, F14.11)', 'Integral= ', temp
    print '(A, ES11.4)', 'discrep= ', abs(temp - exact_integral)
    print *, ' '

    ! Hauss
    M_6 = 2520.26D0
    temp = (1e-7 * 1296.D0)/(5040.D0 * 518400.D0) * M_6
    print '(A)', "Gauss"
    print '(A, F14.11)', 'Integral= ', I_g(0.2D0,0.3D0)
    print '(A, ES11.4)', 'discrep expected= ', temp
    print '(A, ES11.4)', 'discrep= ', abs(I_g(0.2D0,0.3D0) - exact_integral)
    print *, ' '
    
contains

    double precision function f_integrand(x)
        double precision, intent(in) :: x
        f_integrand = asin(sqrt(x)) / sqrt(x*(1.D0 - x))
    end function f_integrand

    double precision function x_val(a, b, N, i)
        double precision, intent(in) :: a, b
        integer, intent(in) :: i, N
        double precision :: h
        h = (b - a) / dble(N)
        x_val = a + dble(i) * h
    end function x_val

    ! Runge
    double precision function I_h(a, b, N)
        double precision, intent(in) :: a, b
        integer, intent(in) :: N
        double precision :: h
        integer :: i

        h = (b - a) / dble(N)
        I_h = 0.D0
        do i = 0, N - 1
            I_h = I_h + f_integrand(x_val(a, b, N, i))
        enddo
        I_h = I_h * h
    end function I_h
    
    ! Trapez
    double precision function I_T(a,b,N)
        double precision, intent(in) :: a, b
        integer, intent(in) :: N
        double precision :: h
        integer :: i

        h = (b - a) / dble(N)
        I_T = 0.D0
        do i = 0, N - 1
            I_T = I_T + (f_integrand(x_val(a, b, N, i)) + f_integrand(x_val(a, b, N, i+1))) / 2.D0
        enddo
        I_T = I_T * h
    end function I_T

    ! Simpson
    double precision function I_C_2(a,b,M_4)
        double precision, intent(in) :: a, b, M_4

        I_C_2=((b-a)/6D0) * (f_integrand(a) + f_integrand(b) + 4D0 * f_integrand((a+b)/2D0)) - ((b-a)**5 / 2880.D0) * M_4
    end function I_C_2

    double precision function I_C(a,b,N)
        double precision, intent(in) :: a, b
        integer, intent(in) :: N
        double precision :: h, fn = 0.D0, fch = 0.D0
        integer:: i
        h = (b-a) / dble(N)
        do i = 1, N / 2
            fn = fn + f_integrand(a + (2.D0 * i - 1.D0) * h)
        enddo

        do i = 1, (N / 2) - 1
            fch = fch + f_integrand(a + 2.D0 * i * h)
        enddo
        I_C = f_integrand(a) + f_integrand(b) + 4.D0*fn + 2.D0*fch
        I_C = I_C * h / 3.D0
    end function I_C

    !Gauss
    double precision function A_i(x)
        double precision, intent(in) :: x
        A_i = 8.D0 / ((1.D0 - x ** 2) * (15.D0 * x ** 2 - 3.D0)**2)
    end function A_i

    double precision function I_g(a,b)
        double precision, intent(in) :: a,b
        double precision :: x0 = 0.D0, x1 = sqrt(3.D0/5.D0), x2
        x2 = -x1
        I_g = 0.D0
        I_g = I_g + A_i(x0) * f_integrand((b+a)/2.D0 + ((b-a)/2.D0)*x0)
        I_g = I_g + A_i(x1) * f_integrand((b+a)/2.D0 + ((b-a)/2.D0)*x1)
        I_g = I_g + A_i(x2) * f_integrand((b+a)/2.D0 + ((b-a)/2.D0)*x2)
        I_g = I_g * (b-a) / 2.D0
    end function I_g
end program lab3
