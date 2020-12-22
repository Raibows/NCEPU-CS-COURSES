<template>
  <div>
    <!--<el-row style="margin-top: 20px;">-->
    <!--<el-col :span="12" :offset="6">-->
    <!--<el-input placeholder="请输入期刊名称（支持模糊搜索）" v-model="keyword" class="input-with-select">-->
    <!--<el-button slot="append" icon="el-icon-search" @click="search"></el-button>-->
    <!--</el-input>-->
    <!--</el-col>-->
    <!--</el-row>-->
    <!--<el-row>-->
    <!--<el-col :span="18" :offset="3" style="margin-top: 20px;">-->
    <!--<el-table-->
    <!--:data="tableData"-->
    <!--border-->
    <!--style="width: 100%">-->
    <!--<el-table-column-->
    <!--fixed-->
    <!--prop="no"-->
    <!--label="编号"-->
    <!--width="150">-->
    <!--</el-table-column>-->
    <!--<el-table-column-->
    <!--prop="journalName"-->
    <!--label="期刊名"-->
    <!--width="120">-->
    <!--</el-table-column>-->
    <!--<el-table-column-->
    <!--prop="startYear"-->
    <!--label="日期"-->
    <!--width="120">-->
    <!--</el-table-column>-->
    <!--<el-table-column-->
    <!--prop="period"-->
    <!--label="期刊类型"-->
    <!--width="120">-->
    <!--</el-table-column>-->
    <!--<el-table-column show-overflow-tooltip-->
    <!--prop="description"-->
    <!--label="描述"-->
    <!--width="300">-->
    <!--</el-table-column>-->
    <!--<el-table-column-->
    <!--fixed="right"-->
    <!--label="操作"-->
    <!--width="100">-->
    <!--<template slot-scope="scope">-->
    <!--<el-button @click="add_journal(scope.row)" type="text" size="small">订阅</el-button>-->
    <!--</template>-->
    <!--</el-table-column>-->
    <!--</el-table>-->
    <!--</el-col>-->
    <!--</el-row>-->
    <el-tabs v-model="activeName" :tab-position="tabPosition" style="height: 70%;padding: 20px;" @tab-click="tabClick">
      <el-tab-pane label="年刊" name="年刊" />
      <el-tab-pane label="月刊" name="月刊" />
      <el-tab-pane label="周刊" name="周刊" />
      <el-tab-pane label="季刊" name="季刊" />

      <div class="block">
        <el-timeline style="width: 60%">
          <el-timeline-item
            v-for="(activity, index) in tableData"
            :key="index"
            placement="top"
            color="lightblue"
            :timestamp="activity.startYear"
          >
            <el-card>
              <el-tag>编号:</el-tag>{{ activity.no }}<br>
              <el-tag>期刊名:</el-tag>{{ activity.journalName }}<br>
              <el-tag>描述:</el-tag>{{ activity.description }}<br>
              <el-button
                type="primary"
                style="margin-top: 20px;position: relative;right: -550px"
                @click="subscribe_journal(activity)"
              >订阅</el-button>
            </el-card>
          </el-timeline-item>
        </el-timeline>
      </div>
    </el-tabs>
    <el-row style="margin-top: 20px;">
      <el-col :span="12" :offset="6">
        <el-pagination
          :current-page="currentPage"
          :page-sizes="[3,5]"
          :page-size="pageSize"
          layout="total, sizes, prev, pager, next, jumper"
          :total="total"
          @size-change="handleSizeChange"
          @current-change="handleCurrentChange"
        />
      </el-col>
    </el-row>
  </div>
</template>

<script>
import { searchJournal } from '@/api/periodical'
import { subscribeJournal } from '../../../api/periodical'

export default {
  name: 'PeriodicalSearch',
  data() {
    return {
      tableData: [],
      activities: [{
        content: '活动按期开始',
        timestamp: '2018-04-15'
      }, {
        content: '通过审核',
        timestamp: '2018-04-13'
      }, {
        content: '创建成功',
        timestamp: '2018-04-11'
      }],
      pageSize: 5,
      currentPage: 1,
      total: 0,
      loading: true,
      tabPosition: 'left',
      selectPeriod: '年刊'
    }
  },
  computed: {},
  created() {
    this.search('年刊')
  },
  methods: {
    search(keyword) {
      searchJournal({
        period: keyword, pageNum: this.currentPage, pageSize: this.pageSize
      }).then(response => {
        this.tableData = response.data.list,
        this.pageSize = response.data.size,
        this.currentPage = response.data.pageNum,
        this.total = response.data.total,
        console.log(this.tableData[0].description)
      })
    },
    handleSizeChange(val) {
      this.pageSize = val
      this.search(this.selectPeriod)
    },
    handleCurrentChange(val) {
      this.currentPage = val
      this.search(this.selectPeriod)
    },
    tabClick(tab, event) {
      this.search(tab.name)
      this.selectPeriod = tab.name
    },
    subscribe_journal(activity) {
      subscribeJournal({ stuId: this.$store.getters.userId, description: activity.description,
        journalName: activity.journalName, journalNo: activity.no, period: activity.period }).then(response => {
        this.$message({
          type: 'success',
          message: response.msg
        })
      })
    }
  }
}
</script>

<style lang="scss" scoped>

</style>
