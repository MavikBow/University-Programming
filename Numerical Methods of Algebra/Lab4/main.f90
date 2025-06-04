program lab4
    implicit none
    double precision, parameter :: a = 0.3D0
    integer, parameter :: N = 11
    double precision, allocatable :: y(:), t(:)
    double precision :: u_0, h
    integer :: i

    h = 1.D0 / dble(N-1)
    u_0 = u_real(a)
    print '(A, F14.11)', 'Exact u_0= ', u_0
    print *, ' '

    allocate(y(N))
    allocate(t(N))

    do i = 1, N
        t(i) = a + (i-1) * h
    enddo

    print *, 't(i)'
    print '(F7.4)', t
    print *, ' '
    print *, 'u(i)'
    do i = 1, N
        print '(F14.11)', u_real(t(i))
    enddo
    print *, ' '

    ! Euler

    y(1) = u_0
    do i = 1, N - 1
        y(i+1) = y(i) + h * du_dt(t(i),y(i))
    enddo

    call print_debug('Euler')

    ! Runge-Kutt

    y(1) = u_0
    do i = 1, N - 1
        y(i+1)=y(i) + h*du_dt(t(i)+h/2.D0,y(i) + h/2.D0*du_dt(t(i),y(i)))
    enddo

    call print_debug('Runge-Kutt')

    ! Adams

    y(1) = u_0
    do i = 1, N - 1
        y(i+1) = newton_method(t(i+1), y(i))
    enddo

    call print_debug('Adams')

    deallocate(y)
    deallocate(t)
    
contains

    double precision function u_real(t)
        double precision, intent(in) :: t
        u_real = t * (a * exp(-t) + (1.D0-a) * sin(t))
    end function u_real

    double precision function du_dt(t,u)
        double precision, intent(in) :: t, u
        du_dt = u/t + t*(-a * exp(-t) + (1.D0-a) * cos(t))
    end function du_dt

    double precision function newton_method(t_next, y_prev)
        double precision, intent(in) :: t_next, y_prev
        double precision :: y_next, F, dF, y_new
        y_next = y_prev
        do
            F = y_next - y_prev - h/2.D0 * (du_dt(t_next, y_next)+ du_dt(t_next - h, y_prev))
            dF = 1.D0 - h / (2.D0 * t_next)
            y_new = y_next - F/dF
            if (abs(y_new - y_next) < h**3) exit
            y_next = y_new
        enddo
        newton_method = y_next
    end function newton_method

    subroutine print_debug(str)
        character(*), intent(in) :: str
        print *, str
        print *, ' '
        print *, 'y(i)'
        do i = 1, N
            print '(F14.11)', y(i)
        enddo
        print *, ' '
        print *, 'r(i)'
        do i = 1, N
            print '(ES11.4)', y(i) - u_real(t(i))
        enddo
        print *, ' '
    end subroutine print_debug

end program lab4
