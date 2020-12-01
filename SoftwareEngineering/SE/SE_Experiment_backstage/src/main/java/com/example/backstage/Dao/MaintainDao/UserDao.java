package com.example.backstage.Dao.MaintainDao;

import com.example.backstage.Entity.MaintainEntity.User;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import javax.transaction.Transactional;
import java.util.List;

@Repository
public interface UserDao extends JpaRepository<User,String> {
    /**
     * @description:通过id查找用户
     * @param id
     * @return
     */
       User findUserById(String id);

    /**
     *@description:通过名字查找用户
     * @param name
     * @return
     */
    @Query(value = "select * from user where name like "+"%"+":name"+"%",nativeQuery = true)
    Page<User> findByNameAs(@Param("name") String name, Pageable pageable);

    /**
     *@description:通过借书号查找用户
     * @param borrowid
     * @return
     */
       User findUserByBorrowid(String borrowid);

    /**
     *@description:检测账号和密码是否正确
     * @param id
     * @param name
     * @return
     */
    User findUserByIdAndPwd(String id,String name);

    /**
     *
     * @return
     */
    @Query(value = "select * from user limit :page,10",nativeQuery = true)
    List<User> findAllByPage(@Param("page") int page);


    /**
     *
     * @param id
     */
    void deleteById(String id);

    /**
     *
     * @param id
     * @return
     */
    String findPwdById(String id);

    /**
     *
     * @return
     */
    @Query(value = "select * from borrow_info where datediff(now(),BorrowDate)>BorrowPeriod",nativeQuery = true)
    List<String> findAllOverdue();


    User findByName(String name);
}
