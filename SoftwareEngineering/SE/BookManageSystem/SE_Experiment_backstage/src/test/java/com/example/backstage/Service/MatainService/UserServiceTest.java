package com.example.backstage.Service.MatainService;

import com.example.backstage.Entity.CatalogueEntity.Temporary;
import com.example.backstage.Entity.MaintainEntity.User;
import lombok.extern.log4j.Log4j2;
import org.junit.Test;
import org.junit.Before; 
import org.junit.After; 
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.context.web.WebAppConfiguration;

import java.util.List;

/** 
* UserService Tester. 
* 
* @author 罗驰
* @since <pre>6月 22, 2020</pre>
* @version 1.0 
*/ 
@RunWith(SpringRunner.class)
@SpringBootTest
@WebAppConfiguration
@Log4j2
public class UserServiceTest {
    @Autowired
    private UserService service;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: findId(String id) 
* 
*/ 
@Test
public void testFindId() throws Exception { 
//TODO: Test goes here...
    log.info(service.findId("201709000616"));
} 

/** 
* 
* Method: findNameLike(String name, Pageable pageable) 
* 
*/ 
@Test
public void testFindNameLike() throws Exception { 
//TODO: Test goes here...
    Pageable pageable=new PageRequest(0,10);
    Page<User> list=service.findNameLike("",pageable);
    log.info(list.getContent());
} 

/** 
* 
* Method: findName(String name) 
* 
*/ 
@Test
public void testFindName() throws Exception { 
//TODO: Test goes here...
   log.info(service.findName("罗驰"));
} 

/** 
* 
* Method: findBorrowId(String borrowid) 
* 
*/ 
@Test
public void testFindBorrowId() throws Exception { 
//TODO: Test goes here...
    log.info(service.findBorrowId("10001"));
} 

/** 
* 
* Method: findAllByPage(int page) 
* 
*/ 
@Test
public void testFindAllByPage() throws Exception { 
//TODO: Test goes here...
    List<User> list=service.findAllByPage(10);
    log.info(list);
} 


/** 
* 
* Method: addUser(User user) 
* 
*/ 
@Test
public void testAddUser() throws Exception { 
//TODO: Test goes here...
    User user=new User("201709000622","李四","男","计算机科学与技术","计科1701","21000",50,"123",
            1,0);
    service.addUser(user);
} 

/** 
* 
* Method: updateUser(User user) 
* 
*/ 
@Test
public void testUpdateUser() throws Exception { 
//TODO: Test goes here...
    User user=new User("201709000622","李四一","男","计算机科学与技术","计科1701","21000",50,"123",
            1,0);
    service.updateUser(user);
} 

/** 
* 
* Method: deleteUser(String id) 
* 
*/ 
@Test
public void testDeleteUser() throws Exception { 
//TODO: Test goes here...
    service.deleteUser("201709000123");
} 


/** 
* 
* Method: findAllOverdue() 
* 
*/ 
@Test
public void testFindAllOverdue() throws Exception { 
//TODO: Test goes here...
    log.info(service.findAllOverdue());
} 


} 
