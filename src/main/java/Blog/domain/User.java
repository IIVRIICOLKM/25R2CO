package Blog.domain;

import jakarta.persistence.*;
import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;

import java.util.Collection;
import java.util.List;

@Table(name = "users")
@NoArgsConstructor
@Getter
@Entity
public class User implements UserDetails {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", updatable = false)
    private Long id;

    @Column(name = "email", nullable = false, unique = true)
    private String email;

    @Column(name = "password")
    private String password;

    @Builder
    public User(String email, String password, String auth){
        this.email = email;
        this.password = password;
    }

    @Override     //권한 반환
    public Collection<? extends GrantedAuthority> getAuthorities(){
        return List.of(new SimpleGrantedAuthority("user"));
    }

    //사용자의 id를 반환(고유한 값)
    @Override
    public String getUsername(){
        return email;
    }

    //사용자의 패스워드 반환
    @Override
    public String getPassword(){
        return password;
    }

    //계정 만료 여부 반환
    @Override
    public boolean isAccountNonExpired(){
        //만료 확인 로직
        return true;
    }

    //계정 잠금 여부 반환
    @Override
    public boolean isAccountNonLocked(){
        //계정 잠금 확인 로직
        return true;
    }

    //패스워드의 만료 여부 반환
    @Override
    public boolean isCredentialsNonExpired(){
        //계정 패스워드 만료 확인 로직
        return true;
    }

    //계정 사용 가능 여부 반환
    @Override
    public boolean isEnabled(){
        //계정 사용 가능 확인 로직
        return true;
    }
}
