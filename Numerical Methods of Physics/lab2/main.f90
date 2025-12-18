program transport_equation
    implicit none

    integer, parameter :: dp = kind(0.0d0)

    ! Параметры сетки
    integer, parameter :: nx = 10          ! x steps (h = 1/10 = 0.1)
    integer, parameter :: nt = 100         ! t steps (tau = 1/100 = 0.01)
    real(dp), parameter :: L = 1.0
    real(dp), parameter :: T_max = 1.0
    real(dp), parameter :: a = 10.0

    real(dp) :: h, tau, Courant
    real(dp), dimension(0:nx) :: u, u_new, x
    real(dp), dimension(0:nx, 0:nt) :: U_matrix
    integer :: i, n, j
    real(dp) :: t_curr

    ! Вычисление шагов
    h = L / nx
    tau = T_max / nt
    Courant = a * tau / h

    print *, "Step h = ", h
    print *, "Step tau = ", tau
    print *, "Courant number = ", Courant

    if (Courant > 1.0) then
        print *, "System is unstable! (C > 1)"
    end if

    ! u(x, 0) = x^2
    do i = 0, nx
        x(i) = i * h
        u(i) = x(i)**2
    end do

    U_matrix = 0.0_dp
    U_matrix(:,0) = u
    u_new = 0.0_dp

    do n = 1, nt
        t_curr = n * tau
        
        ! u(0, t) = 100*t^2
        u_new(0) = 100.0 * (t_curr**2)

        do i = 0, nx - n
            !u_new(i) = (1.0 - Courant) * u(i) + Courant * u(i+1)
            u_new(i) = u(i+1)
        end do
        
        ! attempt when exact value is used as the right border
        !u_new(nx) = (x(nx) + a * t_curr)**2
       
        if (n > nx) exit

        u = u_new
        U_matrix(0:nx-n,n) = u_new(0:nx-n)
    end do

    ! Print U_matrix
    print *, "U matrix"

    do i = nt, 0, -1
        write(*,'(11(f6.3))') (U_matrix(j,i), j = 0, nx)
    end do

    print *, "The difference"
    do i = nx, 0, -1
        write(*,'(11(ES15.6))') (U_matrix(j,i) - u_func(j * h, i * tau), j = 0, nx)
    end do

contains
    function u_func(x, t)
        real(dp) :: u_func
        real(dp), intent(in) :: x, t
        u_func = (x + 10*t)**2
    end function
end program transport_equation
