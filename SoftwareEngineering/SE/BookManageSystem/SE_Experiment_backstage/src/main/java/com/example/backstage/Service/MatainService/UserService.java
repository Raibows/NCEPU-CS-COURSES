package com.example.backstage.Service.MatainService;

import com.example.backstage.Dao.MaintainDao.UserDao;
import com.example.backstage.Entity.MaintainEntity.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.List;

@Service
@Transactional
public class UserService {
    @Autowired
    UserDao userDao;

    /**
     *
     * @param id
     * @return
     */
    public User findId(String id){
        return userDao.findUserById(id);
    }

    /**
     *
     * @param name
     * @return
     */
    public Page<User> findNameLike(String name, Pageable pageable){
        return userDao.findByNameAs(name,pageable);
    }

    /**
     *
     * @param name
     * @return
     */
    public User findName(String name){
        return userDao.findByName(name);
    }

    /**
     *
     * @param borrowid
     * @return
     */
    public User findBorrowId(String borrowid){
        return userDao.findUserByBorrowid(borrowid);
    }

    /**
     *
     * @return
     */
    public List<User> findAllByPage(int page){
       return userDao.findAllByPage(page);
    }


    /**
     *
     * @param user
     * @return
     */
    public User addUser(User user){
        return userDao.save(user);
    }

    /**
     *
     * @param user
     */
    public void updateUser(User user){
          userDao.save(user);
    }

    /**
     *
     * @param id
     */
    public void deleteUser(String id){
        userDao.deleteById(id);
    }


    /**
     *
     * @return
     */
    public List<String> findAllOverdue(){
        return userDao.findAllOverdue();
    }

}
