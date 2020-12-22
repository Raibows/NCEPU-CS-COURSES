package com.example.backstage.Service.InterviewService;

import com.example.backstage.Entity.InterviewEntity.Check;
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

/** 
* CheckService Tester. 
* 
* @author 罗驰
* @since <pre>6月 22, 2020</pre>
* @version 1.0 
*/ 
@RunWith(SpringRunner.class)
@SpringBootTest
@WebAppConfiguration
@Log4j2
public class CheckServiceTest {
    @Autowired
    private CheckService service;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: addCheck(Check check) 
* 
*/ 
@Test
public void testAddCheck() throws Exception { 
//TODO: Test goes here...
    Check check=new Check("20000","abcd","201709000616","hab","1234567895464",10,"");
    service.addCheck(check);
} 

/** 
* 
* Method: findAll(String name, Pageable pageable) 
* 
*/ 
@Test
public void testFindAll() throws Exception { 
//TODO: Test goes here...
    Pageable pageable=new PageRequest(0,10);
    Page<Check> list=service.findAll("",pageable);
    log.info(list.getContent());
} 


} 
