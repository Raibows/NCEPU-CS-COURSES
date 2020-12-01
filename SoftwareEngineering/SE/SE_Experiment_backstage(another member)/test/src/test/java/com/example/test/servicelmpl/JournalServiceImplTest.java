package com.example.test.servicelmpl;

import com.alibaba.fastjson.JSONObject;
import com.example.test.bean.BorrowInfo;
import com.example.test.service.BorrowInfoService;
import com.example.test.service.JournalService;
import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import lombok.extern.log4j.Log4j2;
import lombok.extern.slf4j.Slf4j;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultHandlers;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;

/** 
* JournalServiceImpl Tester. 
* 
* @author <Authors name> 
* @since <pre>6�� 28, 2020</pre> 
* @version 1.0 
*/ 
@Slf4j
@RunWith(SpringRunner.class)
@SpringBootTest
@WebAppConfiguration
@Log4j2
public class JournalServiceImplTest {

    @Autowired
    private JournalService journalService;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: SearchJournal(String period) 
* 
*/ 
@Test
public void testSearchJournal() throws Exception { 
//TODO: Test goes here...
    journalService.SearchJournal("年刊");
} 

/** 
* 
* Method: AddJournal(String no, String journalName, String startYear, String period, String description) 
* 
*/ 
@Test
public void testAddJournal() throws Exception { 
//TODO: Test goes here...
    journalService.AddJournal("1544-3688","好的期刊","1985","年刊","期刊不错！");
} 

/** 
* 
* Method: DeleteJournal(String no) 
* 
*/ 
@Test
public void testDeleteJournal() throws Exception { 
//TODO: Test goes here...
    journalService.DeleteJournal("1544-3698");
} 

/** 
* 
* Method: ModifyJournal(String no, String description, String period) 
* 
*/ 
@Test
public void testModifyJournal() throws Exception { 
//TODO: Test goes here...
    journalService.ModifyJournal("1544-3698","期刊太好了！","月刊");
} 

/** 
* 
* Method: JournalSubscibe(String journalNo, String stuId, String journalName, String period, String description) 
* 
*/ 
@Test
public void testJournalSubscibe() throws Exception { 
//TODO: Test goes here...
    journalService.JournalSubscibe("1544-3688","201709000616","好的期刊","年刊","期刊不错！");
} 

/** 
* 
* Method: JournalCancel(String journalNo, String stuId) 
* 
*/ 
@Test
public void testJournalCancel() throws Exception { 
//TODO: Test goes here...
    journalService.JournalCancel("1544-3698","201709000616");
} 

/** 
* 
* Method: SearchSubscribe(String stuId) 
* 
*/ 
@Test
public void testSearchSubscribe() throws Exception { 
//TODO: Test goes here...
    journalService.SearchSubscribe("201709000616");
} 


} 
