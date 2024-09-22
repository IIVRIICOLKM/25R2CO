package Blog.Config.jwt;

import Blog.config.jwt.JwtProperties;
import Blog.config.jwt.TokenProvider;
import Blog.repository.UserRepository;
import io.jsonwebtoken.Jwt;
import io.jsonwebtoken.Jwts;
import org.assertj.core.api.Assertions;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import Blog.domain.User;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.userdetails.UserDetails;

import java.time.Duration;
import java.util.Date;
import java.util.Map;

@SpringBootTest
class TokenProviderTest {
    @Autowired
    private TokenProvider tokenProvider;
    @Autowired
    private UserRepository userRepository;
    @Autowired
    private JwtProperties jwtProperties;

    //generationToken() 검증 테스트
    @DisplayName("generationToken() : 유저 정보와 만료 기간을 전달해 토큰을 만들 수 있다.")
    @Test
    void generationToken(){
        //given - 테스트 사용자 제작
        User testUser = userRepository.save(User.builder()
                .email("user@gmail.com").password("test").build());
        //when - 테스트 토큰 생성
        String token = tokenProvider.generateToken(testUser, Duration.ofDays(14));
        //then - 토큰 복호화 후, id 추출
        Long userId = Jwts.parser()
                .setSigningKey(jwtProperties.getSecretKey())
                .parseClaimsJws(token)
                .getBody()
                .get("id", Long.class);
        Assertions.assertThat(userId).isEqualTo(testUser.getId());
    }

    // validToken() 검정 테스트
    @DisplayName("validToken() : 토큰 만료 시 유효성 검증 실패")
    @Test
    void validToken_invalidToken(){
        //given - 만료된 토큰 생성(getTime() - )
        String token = JwtFactory.builder().expiration(new Date(
                new Date().getTime() - Duration.ofDays(7).toMillis()))
                .build().createToken(jwtProperties);
        //when - 유효성 검증(원본 파일의 메서드 직접 추가)
        boolean result = tokenProvider.validToken(token);
        //then
        Assertions.assertThat(result).isFalse();
    }

    @DisplayName("validToken() : 유효한 토큰인 때 유효성 검증 성공")
    @Test
    void validToken_validToken(){
        //given - 만료되지 않은 토큰 생성(유효기간 14일)
        String token = JwtFactory.withDefaultValues().createToken(jwtProperties);
        //when
        boolean result = tokenProvider.validToken(token);
        //then
        Assertions.assertThat(result).isTrue();
    }

    @DisplayName("getAuthentication() : 검증 테스트")
    @Test
    void getAuthentication(){
        //given
        String userEmail = "user@email.com";
        String token = JwtFactory.builder()
                .subject(userEmail)
                .build()
                .createToken(jwtProperties);
        //when
        Authentication authentication = tokenProvider.getAuthentication(token);
        //then (이메일이 서로 같은 지 확인)
        Assertions.assertThat(((UserDetails) authentication
                .getPrincipal()).getUsername())
                .isEqualTo(userEmail);
    }

    @DisplayName("getUserId() : 토큰으로 유저 ID를 가져올 수 있다.")
    @Test
    void getUserId(){
        //given
        Long userId = 1L;
        String token = JwtFactory.builder()
                .claims(Map.of("id", userId))
                .build()
                .createToken(jwtProperties);
        //when
        Long userIdByToken = tokenProvider.getUserId(token);
        //then
        Assertions.assertThat(userIdByToken).isEqualTo(userId);
    }
}
